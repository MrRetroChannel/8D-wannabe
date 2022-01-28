#include "SoundBuffer.h"
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>
#include <iostream>
SoundBuffer::SoundBuffer()
{
	alDeleteBuffers(soundbuf.size(), soundbuf.data());
	soundbuf.clear();
}

SoundBuffer::~SoundBuffer()
{
	alDeleteBuffers(soundbuf.size(), soundbuf.data());
	soundbuf.clear();
}

SoundBuffer* SoundBuffer::get()
{
	static SoundBuffer* sound = new SoundBuffer;
	return sound;
}

ALuint SoundBuffer::AddSoundEffect(const char* file)
{
	ALenum err, format;
	ALuint buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;

	sndfile = sf_open(file, SFM_READ, &sfinfo);


	format = AL_FORMAT_MONO16;
	/*if (sfinfo.channels == 1)
		format = AL_FORMAT_MONO16;
	
	else if (sfinfo.channels == 2)
		format = AL_FORMAT_STEREO16;

	else if (sfinfo.channels == 3)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (sfinfo.channels == 4)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT3D_16;
	} */ 
	if (!format)
	{
		fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
		sf_close(sndfile);
		return 0;
	}
	membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if (num_frames < 1)
	{
		free(membuf);
		sf_close(sndfile);
		fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", file, num_frames);
		return 0;
	}
	num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

	free(membuf);
	sf_close(sndfile);


	err = alGetError();
	if (err != AL_NO_ERROR)
	{
		fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		if (buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
		return 0;
	}


	soundbuf.push_back(buffer);
	return buffer;	
}



bool SoundBuffer::removeSoundEffect(const ALuint& buf)
{
	for (auto i = soundbuf.begin(); i != soundbuf.end();)
	{
		if (*i == buf)
		{
			alDeleteBuffers(1, &*i);
			i = soundbuf.erase(i);
			return true;
		}
		else
			i++;
	}
	return false;
}
