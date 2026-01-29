//
// Book - Rhian Omos (homage)
// Describes a short ritual for a good-aligned non-member to pay homage
// to the dieties of sean-rhian. A player can increase alignment by one
// point, once per login, by properly completing the ceremony.
// Zima April 2007
//
#include <alignment.h>
#include <macros.h>
#include "defs.h"
#define  CHANT_TIME 4.0
inherit SR_BOOK_BASE;

static string verse1, verse2, diety;
static int    cantNum, step=0;

// 
// create_book()
//
void create_book() {
    title="Rhian Omos";
    set_short("black cloth-bound book");
    add_name(({SR_OMOS_BOOK,lower_case(title)}));
    add_adj(({"cloth-bound","black","small"}));
    set_long("It is a small, black, cloth-bound book entitled: "+title+".\n");
    set_lpp(21);      // lines per page
    set_max_pages(3);
    set_sr_level(-1); // for the public
    set_book_file("omos.txt");
} // create_book()

//
// do_chant()
//
void do_chant() {
    object room = ENV(TP), ped, altar, stick;
    int    omos_prop, align;
    step++;
       
    // if step 1,2 just show messages
    switch (step) {
    case 1: write("You chant: " + verse1);
            tell_room(room,QCTNAME(TP)+ " chants: " + verse1,TP);         
            set_alarm(CHANT_TIME,0.0,&do_chant()); 
            return;
    case 2: write("You chant: " + verse2);
            tell_room(room,QCTNAME(TP)+ " chants: " + verse2,TP);         
            set_alarm(CHANT_TIME,0.0,&do_chant()); 
            return;            
    case 3: break; // continue below
    default: return;        
    }
    
    // step 3: reponse step
    // check for burning incense, reset step to 0 if error
    step = 0; // reset for next chant   
    if (cantNum < 11) { // incense should be on pedestal
        if (cantNum < 10)
            ped = present(diety+SR_PEDESTAL,room);            
        else // canticle 10
            ped = room;      
        if (!objectp(ped)) return;       
        stick = present(SR_STICK_INCENSE,ped);      
        if (!objectp(stick)) return;  
        if (!stick->query_lit()) return;       
    }
    
    // check rite property
    omos_prop = TP->query_prop(SR_OMOS_PROP);   
    if (!omos_prop) return;  //did not start with holy water sprinkle
    omos_prop = omos_prop | (1 << cantNum); // set bit for this diety

    // show a response to the player
    switch (cantNum) {
    case 11: altar = present(SR_ALTAR,room);       
             if (!altar) return;            
             if (omos_prop == 4095) { // 0x0FFF, rightmost 12 bits set                
                 tell_room(room,"The candles of the chandeliers above flare "+
                           "brightly, then mysteriously return to normal.\n");
                 align = TP->query_alignment();
                 TP->remove_prop(SR_OMOS_PROP);                 
                 if ((!TP->query_prop(SR_OMOS_DONE_PROP)) && align<ALIGN_MAX) {
//                     TP->set_alignment(align + 1);
                     TP->add_prop(SR_OMOS_DONE_PROP,1); // limit once per login
                     write("The power of Order and Holiness cascades down "+
                           "upon you.\n");
                     log_file("alignment_quest", ctime(time()) + " " + 
                              TP->query_name() + " " + align + "->"  +
                              TP->query_alignment() + "\n");
                 }
             }           
             break;
    case 10: tell_room(room,"The torch held by the statue glows mysteriously.\n");
             TP->add_prop(SR_OMOS_PROP,omos_prop);
             break;
    default: tell_room(room,"Sunlight briefly brightens the image on the window.\n");
             TP->add_prop(SR_OMOS_PROP,omos_prop);
             break;
    }
} // do_chant()

// 
// try_chant() - player tries to chant
//
int try_chant(string cmd) {
   int canticleNumber;
   object ob, room, ped1, ped2;
   object *inv=all_inventory(TP);
   string verb=query_verb();
   notify_fail(verb+" what? chant canticle 1?\n");
   
   // one chant at a time please
   if (step != 0) {
       write("Patience child!\n");
       return 1;
   }   
   
   // validate canticle number
   if (!stringp(cmd)) return 0;
   canticleNumber = 0;
   if (!parse_command(cmd,inv," 'canticle' %d ",canticleNumber)) 
       return 0;
   if (canticleNumber < 1 || canticleNumber > 11) {
       write("There are eleven canticles, 1 through 11\n");
       return 1;
   }
   cantNum = canticleNumber;
   
   // setup chant verses and related items based on chant#
   // note: messages should be the same as in sean-rhian/book/text/omos.txt
   switch (canticleNumber) {
   case 1: verse1 = "Glory be to he who holds the staff of wisdom!\n"; 
           verse2 = "May he guide me in my travels.\n";
           diety  = SR_CAMULOS;
           break;
   case 2: verse1 = "Glory be to the verdant mother!\n"; 
           verse2 = "May her blessing heal my wounded soul.\n";
           diety  = SR_KESAIR;
           break;   
   case 3: verse1 = "Glory be to the master of the flames!\n";
           verse2 = "May his power purify me as gold.\n";
           diety  = SR_IRGALACH;          
           break;
   case 4: verse1 = "Glory be to the conqueror of chaos!\n";
           verse2 = "May his courage strengthen mine.\n";
           diety = SR_AMBISARGUS;          
           break;
   case 5: verse1 = "Glory be to the high priest of Ardaugh!\n";
           verse2 = "May his blessings fall upon me.\n";
           diety  = SR_SEANCHAN_TOR;         
           break;
   case 6: verse1 = "Glory be to the princess of the heavens!\n";
           verse2 = "May her winds sail me to good fortune.\n";
           diety = SR_RHIANNON;         
           break;
   case 7: verse1 = "Glory be to the guardian of the night!\n";
           verse2 = "May his light lead me through darkness.\n";
           diety = SR_RAGALLACH;        
           break;
   case 8: verse1 = "Glory be to the lord of smiths!\n";
           verse2 = "May he mold me in the image of goodness.\n";
           diety  = SR_SECHNASACH;
           break;
   case 9: verse1 = "Glory be to the mistress of the forest!\n";
           verse2 = "May she protect me from the danger within.\n";
           diety = SR_ARGANTE;
           break;
   case 10:verse1 = "Glory be to the Archangel of Ardaugh!\n";
           verse2 = "May his words bring order to the world.\n";
           diety = SR_MAIGHAL;          
           break;           
   case 11:verse1 = "All glory and praise to Ardaugh the Most High!\n";
           verse2 = "It is a privilege to praise him.\n";
           diety  = SR_ARDAUGH;
   }   
   do_chant();
   return 1;    
} // try_chant()

//
// init()
//
void init() {
    ::init();
    add_action(&try_chant(), "chant");
} // init()
