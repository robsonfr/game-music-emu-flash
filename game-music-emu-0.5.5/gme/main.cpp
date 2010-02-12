#include "main.h"

//static char filename [] = "test.nsf"; /* opens this file (can be any music type) */
Music_Emu* musicEmu = 0;
short* buf = 0;

//entry point for code
int main(int argc, char* argv[])
{
	buf = (short *)malloc(8192 * 2 * 2);
	if (!buf) {
		handleError("out of memory");
	}

	//define the methods exposed to ActionScript
	//typed as an ActionScript Function instance
	AS3_Val loadMethod = AS3_Function(NULL, load);
	AS3_Val initAyMethod = AS3_Function(NULL, initAy);
	AS3_Val initGbsMethod = AS3_Function(NULL, initGbs);
	AS3_Val initGymMethod = AS3_Function(NULL, initGym);
	AS3_Val initHesMethod = AS3_Function(NULL, initHes);
	AS3_Val initKssMethod = AS3_Function(NULL, initKss);
	AS3_Val initNsfMethod = AS3_Function(NULL, initNsf);
	AS3_Val initNsfeMethod = AS3_Function(NULL, initNsfe);
	AS3_Val initSapMethod = AS3_Function(NULL, initSap);
	AS3_Val initSpcMethod = AS3_Function(NULL, initSpc);
	AS3_Val initVgmMethod = AS3_Function(NULL, initVgm);
	AS3_Val initVgzMethod = AS3_Function(NULL, initVgz);
	AS3_Val playMethod = AS3_Function(NULL, play);
	AS3_Val stopMethod = AS3_Function(NULL, stop);
	AS3_Val tellMethod = AS3_Function(NULL, tell);
	AS3_Val seekMethod = AS3_Function(NULL, seek);
	AS3_Val setTempoMethod = AS3_Function(NULL, setTempo);
	AS3_Val setFadeMethod = AS3_Function(NULL, setFade);
	AS3_Val setStereoDepthMethod = AS3_Function(NULL, setStereoDepth);
	AS3_Val trackInfoMethod = AS3_Function(NULL, trackInfo);
	AS3_Val startTrackMethod = AS3_Function(NULL, startTrack);
	AS3_Val trackCountMethod = AS3_Function(NULL, trackCount);
	AS3_Val trackEndedMethod = AS3_Function(NULL, trackEnded);

	// construct an object that holds references to the functions
	AS3_Val result = AS3_Object("load: AS3ValType,"
								"initAy: AS3ValType,"
								"initGbs: AS3ValType,"
								"initGym: AS3ValType,"
								"initHes: AS3ValType,"
								"initKss: AS3ValType,"
								"initNsf: AS3ValType,"
								"initNsfe: AS3ValType,"
								"initSap: AS3ValType,"
								"initSpc: AS3ValType,"
								"initVgm: AS3ValType,"
								"initVgz: AS3ValType,"
								"play: AS3ValType,"
								"stop: AS3ValType,"
								"tell: AS3ValType,"
								"seek: AS3ValType,"
								"setTempo: AS3ValType,"
								"setFade: AS3ValType,"
								"setStereoDepth: AS3ValType,"
								"trackInfo: AS3ValType,"
								"startTrack: AS3ValType,"
								"trackCount: AS3ValType,"
								"trackEnded: AS3ValType",
								
								loadMethod,
								initAyMethod,
								initGbsMethod,
								initGymMethod,
								initHesMethod,
								initKssMethod,
								initNsfMethod,
								initNsfeMethod,
								initSapMethod,
								initSpcMethod,
								initVgmMethod,
								initVgzMethod,
								playMethod,
								stopMethod,
								tellMethod,
								seekMethod,
								setTempoMethod,
								setFadeMethod,
								setStereoDepthMethod,
								trackInfoMethod,
								startTrackMethod,
								trackCountMethod,
								trackEndedMethod);

	// Release
	AS3_Release(loadMethod);
	AS3_Release(initAyMethod);
	AS3_Release(initGbsMethod);
	AS3_Release(initGymMethod);
	AS3_Release(initHesMethod);
	AS3_Release(initKssMethod);
	AS3_Release(initNsfMethod);
	AS3_Release(initNsfeMethod);
	AS3_Release(initSapMethod);
	AS3_Release(initSpcMethod);
	AS3_Release(initVgmMethod);
	AS3_Release(initVgzMethod);
	AS3_Release(playMethod);
	AS3_Release(stopMethod);
	AS3_Release(tellMethod);
	AS3_Release(seekMethod);
	AS3_Release(setTempoMethod);
	AS3_Release(setFadeMethod);
	AS3_Release(setStereoDepthMethod);
	AS3_Release(trackInfoMethod);
	AS3_Release(startTrackMethod);
	AS3_Release(trackCountMethod);
	AS3_Release(trackEndedMethod);

	// notify that we initialized -- THIS DOES NOT RETURN!
	AS3_LibInit(result);

	// should never get here!
	return 0;
}

void handleError(const char* str)
{
	if ( str )
	{
		fprintf(stderr, "[game-music-emu Error]: %s", str);
		exit(EXIT_FAILURE);
	}
}

static AS3_Val load(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(load) not inited music emu.");
	}

	AS3_Val byteArray = AS3_Undefined();
	int len = 0;

	AS3_ArrayValue(args, 
				   "AS3ValType,"
				   "IntType", 
				   &byteArray, 
				   &len);
	
	unsigned char *data = 0;
	data = (unsigned char *)malloc(len);
	if (!data) {
		handleError("out of memory");
	}
	
	int ret;
	ret = AS3_ByteArray_readBytes(data, byteArray, len);
	
	/* index of track to play (0 = first) */
	int track = 0;
	
	//handleError( gme_open_file(filename, &emu, sample_rate) );
	handleError( gme_load_data(musicEmu, data, len) );
	
	/* Start track */
	handleError( gme_start_track(musicEmu, track) );
	
	free(data);
	return AS3_Null();
}

static AS3_Val startTrack(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(startTrack) not inited music emu.");
	}
	
	int track = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &track);
	handleError( gme_start_track(musicEmu, track) );
	return AS3_Null();
}

static AS3_Val trackCount(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(trackCount) not inited music emu.");
	}
	return AS3_Int(gme_track_count(musicEmu));
}

static AS3_Val trackEnded(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(trackEnded) not inited music emu.");
	}
	return AS3_Int(gme_track_ended(musicEmu));
}

static AS3_Val trackInfo(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(trackInfo) not inited music emu.");
	}
	
	int track = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &track);
	
	gme_info_t* info;
	handleError( gme_track_info(musicEmu, &info, track) );
	
	AS3_Val ret = AS3_Object("system:StrType,"
							"game:StrType,"
							"song:StrType,"
							"author:StrType,"
							"copyright:StrType,"
							"comment:StrType,"
							"dumper:StrType,"
							"length:IntType,"
							"intro_length:IntType,"
							"loop_length:IntType,"
							"play_length:IntType",
							
							info->system,
							info->game,
							info->song,
							info->author,
							info->copyright,
							info->comment,
							info->dumper,
							info->length,
							info->intro_length,
							info->loop_length,
							info->play_length);
	gme_free_info(info);
	return ret;
}

static AS3_Val tell(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(tell) not inited music emu.");
	}
	return AS3_Int(gme_tell(musicEmu));
}

static AS3_Val seek(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(seek) not inited music emu.");
	}
	
	int msec = 0;
	AS3_ArrayValue(args,
				   "IntType",
				   &msec);
	handleError( gme_seek(musicEmu, msec) );
	return AS3_Null();
}

static AS3_Val stop(void* self, AS3_Val args)
{
	/* Cleanup */
	freeMusicEmu();
	//freeBuffer();
	
	//wave_close();
	return AS3_Null();
}

static AS3_Val play(void* self, AS3_Val args)
{
	AS3_Val byteArray = AS3_Undefined();
	int samples = 0;

	AS3_ArrayValue(args, "AS3ValType,"
						 "IntType", 
						 &byteArray, 
						 &samples);
	
	/* limit */
	if (samples > 8192) {
		samples = 8192;
	}
	
	/* Sample buffer */
	//#define buf_size 1024 /* can be any multiple of 2 */
	samples *= 2;
	
	/* Fill sample buffer */
	handleError( gme_play(musicEmu, samples, buf) );
	
	AS3_ByteArray_writeBytes(byteArray, buf, samples * 2);
	
	return AS3_Null();
}

static AS3_Val setTempo(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(setTempo) not inited music emu.");
	}
	
	double tempo = 0;
	AS3_ArrayValue(args, 
				   "DoubleType", 
				   &tempo);
	gme_set_tempo(musicEmu, tempo);
	
	return AS3_Null();
}

static AS3_Val setFade(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(setFade) not inited music emu.");
	}
	
	int start_msec = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &start_msec);
	gme_set_fade(musicEmu, start_msec);
	
	return AS3_Null();
}

static AS3_Val setStereoDepth(void* self, AS3_Val args)
{
	if (musicEmu == 0) {
		handleError("(setFade) not inited music emu.");
	}
	
	double depth = 0;
	AS3_ArrayValue(args, 
				   "DoubleType", 
				   &depth);
	gme_set_stereo_depth(musicEmu, depth);
	
	return AS3_Null();
}

// ----------------------------------------------------------------------------


static AS3_Val initAy(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_ay_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initGbs(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_gbs_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initGym(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_gym_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initHes(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_hes_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initKss(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_kss_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initNsf(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_nsf_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initNsfe(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_nsfe_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initSap(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_sap_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initSpc(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_spc_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initVgm(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_vgm_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}

static AS3_Val initVgz(void* self, AS3_Val args)
{
	// load args
	int sample_rate = 0;
	AS3_ArrayValue(args, 
				   "IntType", 
				   &sample_rate);
	
	freeMusicEmu();
	musicEmu = gme_new_emu(gme_vgz_type, sample_rate);
	
	if (musicEmu == 0) {
		handleError("out of memory");
	}
	
	return AS3_Null();
}


void freeMusicEmu()
{
	if (musicEmu != 0) {
		gme_delete(musicEmu);
		musicEmu = 0;
	}
}

void freeBuffer()
{
	if (buf != 0) {
		free(buf);
	}
}

