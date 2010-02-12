#include <stdlib.h>
#include <stdio.h>

#include "AS3.h"
#include "gme.h"
//#include "Spc_Emu.h"
//#include "Nsf_Emu.h"

void freeMusicEmu();
void freeBuffer();

void handleError(const char* str);

static AS3_Val load(void* self, AS3_Val args);
static AS3_Val stop(void* self, AS3_Val args);
static AS3_Val play(void* self, AS3_Val args);

static AS3_Val trackInfo(void* self, AS3_Val args);
static AS3_Val startTrack(void* self, AS3_Val args);
static AS3_Val trackCount(void* self, AS3_Val args);
static AS3_Val trackEnded(void* self, AS3_Val args);
static AS3_Val tell(void* self, AS3_Val args);
static AS3_Val seek(void* self, AS3_Val args);
static AS3_Val setTempo(void* self, AS3_Val args);
static AS3_Val setFade(void* self, AS3_Val args);
static AS3_Val setStereoDepth(void* self, AS3_Val args);

static AS3_Val initAy(void* self, AS3_Val args);
static AS3_Val initGbs(void* self, AS3_Val args);
static AS3_Val initGym(void* self, AS3_Val args);
static AS3_Val initHes(void* self, AS3_Val args);
static AS3_Val initKss(void* self, AS3_Val args);
static AS3_Val initNsf(void* self, AS3_Val args);
static AS3_Val initNsfe(void* self, AS3_Val args);
static AS3_Val initSap(void* self, AS3_Val args);
static AS3_Val initSpc(void* self, AS3_Val args);
static AS3_Val initVgm(void* self, AS3_Val args);
static AS3_Val initVgz(void* self, AS3_Val args);

int main(int argc, char* argv[]);
