#include "Info.h"
#include "gui.h"

#include "pushpull.h"

static const uint16_t imagedata[1024] = {
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0043,0x0064,0x0064,0x0064,0x0022,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0042,0x00e9,0x01f1,0x12b5,0x2338,0x3bd9,0x3bd9,0x2b78,0x1ad6,0x0a53,0x014d,0x0085,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0022,0x016c,0x2337,0x5c9c,0x8dbd,0xa61d,0xae5d,0xb67d,0xb67d,0xb65d,0xa63d,0x9dfd,0x6d1c,0x33da,0x0a11,0x0085,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00e9,0x1af6,0x64dc,0xa61d,0xb67d,0xa61d,0x8dbc,0x855c,0x7d3c,0x7d3c,0x7d5c,0x8d9c,0x9dfd,0xae5d,0xb65d,0x857d,0x3399,0x018f,0x0021,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x018d,0x3bfa,0x9dfd,0xae5d,0x8d9c,0x6cfb,0x64bb,0x5cbb,0x64bb,0x64bb,0x64bb,0x5c9b,0x5c9b,0x5c9b,0x6cdb,0x7d5c,0xa61d,0xae5d,0x6cfc,0x0a74,0x0043,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x018e,0x547b,0xae3d,0x95dd,0x6cfc,0x5cbb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5cbb,0x751c,0x95dd,0x7d3c,0x5cbb,0x5cbb,0x64db,0x857c,0xae5d,0x7d5d,0x1295,0x0043,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x012b,0x443b,0xae3d,0x857c,0x5cbb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5cbb,0x7d3c,0xef9f,0xffff,0xf7df,0x8d9c,0x5c9b,0x64bb,0x5cbb,0x6cfb,0xa61d,0x7d5d,0x0a73,0x0021,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0086,0x3399,0xa61d,0x7d3c,0x5cbb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5c9b,0xb67d,0xffff,0xffff,0xffff,0xc6de,0x5cbb,0x64bb,0x64bb,0x64bb,0x6cdb,0xa61d,0x64dc,0x018e,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0a53,0x859d,0x857c,0x5cbb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5c9b,0x9dfd,0xffff,0xffff,0xffff,0xb65d,0x5c9b,0x64bb,0x64bb,0x64bb,0x64bb,0x6cfb,0x9dfd,0x33b9,0x0085,0x0000,0x0000,
		0x0000,0x0000,0x00c8,0x4c3b,0x95bd,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0xb67d,0xe75f,0xbebe,0x6cfb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5cbb,0x7d5c,0x7d5d,0x01f1,0x0000,0x0000,
		0x0000,0x0000,0x0a11,0x857d,0x6cfc,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5c9b,0x64db,0x5cbb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x8dbd,0x3399,0x0064,0x0000,
		0x0000,0x0043,0x2b58,0x857c,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5cbb,0x5c9b,0x5c9b,0x5c9b,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x547b,0x64bb,0x443b,0x010b,0x0000,
		0x0000,0x00c8,0x4c5b,0x751c,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64db,0x7d5c,0x8dbc,0xa61d,0xbe9e,0xdf3e,0xa61d,0x5c9b,0x64bb,0x64bb,0x64bb,0x5c9b,0x547b,0x443a,0x3bfa,0x441a,0x549b,0x01f1,0x0000,
		0x0000,0x014c,0x549c,0x6cdb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5cbb,0x857c,0xcefe,0xffff,0xffff,0xffff,0xffff,0x95bd,0x5cbb,0x64bb,0x547b,0x4c5b,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x4c5b,0x0a75,0x0021,
		0x0000,0x09ef,0x64dc,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x6cdb,0xe77f,0xffff,0xffff,0xefbf,0x6cdb,0x547b,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x443b,0x12f7,0x0043,
		0x0000,0x0a11,0x5cbc,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x74fc,0xf7bf,0xffff,0xffff,0xbe9e,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441b,0x1af7,0x0063,
		0x0000,0x1231,0x5c9c,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5c9b,0x95dd,0xffff,0xffff,0xffff,0x857c,0x33da,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3c1a,0x12d7,0x0063,
		0x0000,0x11ce,0x4c5b,0x64db,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x547b,0x443a,0xb67d,0xffff,0xffff,0xf7bf,0x547b,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x3bfa,0x12b6,0x0042,
		0x0000,0x094a,0x443b,0x64db,0x64bb,0x64bb,0x64bb,0x64bb,0x64bb,0x5c9b,0x545b,0x441a,0x3bfa,0x4c3a,0xef9f,0xffff,0xffff,0xc6be,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x33da,0x1274,0x0000,
		0x0000,0x00c6,0x33ba,0x64bb,0x64bb,0x64bb,0x64bb,0x547b,0x4c3b,0x441a,0x3bfa,0x3bfa,0x3bda,0x7d3c,0xffff,0xffff,0xffff,0x8dbc,0x33da,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x2bba,0x11ef,0x0000,
		0x0000,0x0021,0x22f5,0x5c9c,0x5c9b,0x4c5b,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0xb67d,0xffff,0xffff,0xf7df,0x5c9b,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x237a,0x08e7,0x0000,
		0x0000,0x0000,0x11cd,0x3bfb,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x4c5b,0xef9f,0xffff,0xffff,0xd71e,0x3bfa,0x441a,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x3bfa,0x1ad5,0x0021,0x0000,
		0x0000,0x0000,0x0063,0x2337,0x3c1a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bda,0x751c,0xffff,0xffff,0xffff,0x95dd,0x3bfa,0x9dfd,0x545b,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x33ba,0x116b,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x118c,0x33db,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0xa63d,0xffff,0xffff,0xffff,0x8d9c,0xa5fd,0x7d3c,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x3c1b,0x1ad5,0x0021,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0021,0x1a93,0x441b,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0xae5d,0xffff,0xffff,0xffff,0xf7df,0x8dbc,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x443b,0x2b79,0x08c6,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0063,0x22f6,0x443b,0x4c3a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x5c9b,0xcefe,0xef9f,0xd71e,0x7d3c,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x4c5b,0x33ba,0x096a,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0084,0x22f6,0x443b,0x4c5b,0x441a,0x3bfa,0x3bfa,0x3bfa,0x441a,0x4c5b,0x43fa,0x3bda,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x4c5b,0x4c5b,0x33ba,0x098b,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0063,0x1a72,0x3bfb,0x4c5b,0x4c5b,0x443a,0x441a,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x3bfa,0x441a,0x4c3b,0x545b,0x443b,0x2337,0x0929,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x096a,0x22f6,0x3bfb,0x4c7b,0x547b,0x547b,0x4c5b,0x4c5b,0x4c5b,0x4c5b,0x545b,0x547b,0x547b,0x443b,0x2b78,0x120f,0x0063,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0042,0x098b,0x1ab4,0x2b78,0x3bfb,0x443b,0x443b,0x443b,0x443b,0x3c1b,0x33ba,0x2316,0x120f,0x00a5,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0084,0x0908,0x11ad,0x11ee,0x11ee,0x11ce,0x094a,0x00c6,0x0042,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

static Image_t icon = { .width = 32, .height = 32, .data = imagedata };

/* Forward declaration of actual app task */
static void Info(void *unused);

/* Creates the app task, called from desktop when user start the app */
static void Info_Start(){
	xTaskCreate(Info, "Info", 300, NULL, 3, NULL);
}

/* Register this app */
void Info_Init() {
	App_Register("Info", Info_Start, icon);
}

static void Info(void *unused) {
	/* Create GUI elements */
	container_t *c= container_new(COORDS(280, 240));
	c->base.position.x = 40;

	label_t *lTemp = label_newWithText("Temperature:", Font_Big);
	label_t *lHeap = label_newWithText("Free HEAP:", Font_Big);
	label_t *lDiss = label_newWithText("Int. Dissipat.:", Font_Big);

	int32_t heap;
	int32_t temp;
	int32_t dissipation;

	entry_t *eTemp = entry_new(&temp, NULL, NULL, Font_Big, 6, &Unit_Temperature);
	entry_t *eHeap = entry_new(&heap, NULL, NULL, Font_Big, 6, &Unit_Memory);
	entry_t *eDiss = entry_new(&dissipation, NULL, NULL, Font_Big, 6, &Unit_Power);

	container_attach(c, (widget_t*) lTemp, COORDS(5, 5));
	container_attach(c, (widget_t*) eTemp, COORDS(200, 5));
	container_attach(c, (widget_t*) lHeap, COORDS(5, 30));
	container_attach(c, (widget_t*) eHeap, COORDS(200, 30));
	container_attach(c, (widget_t*) lDiss, COORDS(5, 55));
	container_attach(c, (widget_t*) eDiss, COORDS(200, 55));

	/* Notify desktop of started app */
	desktop_AppStarted(Info_Start, (widget_t*) c);

	while(1) {

		heap = xPortGetFreeHeapSize();
		temp = pushpull_GetTemperature();

		/* calculate internal dissipation */
		// TODO instead of fixed 24V use measured 24V rail if adjustable rail is used
		if(pushpull_GetEnabled()) {
			/* Output is on, dissipation depends mainly on current */
			if(pushpull_GetCurrent()>0) {
				/* Sourcing current */
				dissipation = (int64_t) pushpull_GetCurrent()
						* (24000000 - pushpull_GetBatteryVoltage()) / 1000000;
			} else {
				/* Sinking current */
				dissipation = (int64_t) -pushpull_GetCurrent()
						* pushpull_GetBatteryVoltage() / 1000000;
			}
		} else {
			/* Output off */
			/* Dissipation is only the bias current */
			dissipation = pushpull_GetBiasCurrent() * (24000000/1000000);
		}

		widget_RequestRedraw((widget_t*) eTemp);
		widget_RequestRedraw((widget_t*) eHeap);
		widget_RequestRedraw((widget_t*) eDiss);

		uint32_t signal;
		if (App_Handler(&signal, 300)) {
			/* Handle app signals */
		}
	}
}