#ifndef KHALAKHOR_ASHLAGH_SHIPLINE
#define KHALAKHOR_ASHLAGH_SHIPLINE
 
#define PARENT         "/d/Khalakhor/"
#define SE_SPEIR       PARENT      + "se_speir/"
#define PORT_MACDUNN   SE_SPEIR    + "port/"
 
#define ASHLAGH_PIER   SE_SPEIR    + "lohrayn/ashlagh/room/pier"
 
#define SHIP_DIR       PARENT      + "ship/"
#define MACDUNN_DIR    SHIP_DIR    + "macdunn/"
#define THIS_DIR       MACDUNN_DIR + "ashlagh/"
 
#define OBJ_DIR        THIS_DIR
#define MONSTER        THIS_DIR
 
#define CABIN          THIS_DIR    + "cabin"
#define DECK           THIS_DIR    + "deck"
#define CAPTAIN        THIS_DIR    + "captain"
#define TICKET         OBJ_DIR     + "ticket"
#define TICKET_NAME    "the MacDunn-Baile Ashlagh line"
#define SHIP_NAME      "Aigne Deas"
#define PRICE          20
 
#endif
