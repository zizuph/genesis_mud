

inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

#define NUM_ROBES   10
#define NUM_MANTLES 5
#define NUM_INCENSE 10
#define NUM_ALBS    5
#define NUM_TOMES   1
#define NUM_JOIN    1 
#define NUM_OILS    1
#define NUM_WEDB    1
#define NUM_CHAL    1
#define NUM_BREAD   1
#define NUM_DRUMS   2
#define NUM_BELLS   2
#define NUM_CHIMES  2
#define NUM_CANDLES 10
 
void 
load_cabinet_item(string path, int num, object obj)
{
    int i;
    object *cobj=allocate(num);
    seteuid(getuid());

    for (i=0; i < num; i++)
    {
        cobj[i]=clone_object(path);
        cobj[i]->move(obj);
    }
}
 
void 
load_cabinet(object obj) 
{
    obj->add_prop(CONT_I_CLOSED,0); /* open cabinet to load */
    load_cabinet_item((SPIRIT_OBJECTS+"robe"),             NUM_ROBES,   obj);
    load_cabinet_item((SPIRIT_OBJECTS+"mantle"),           NUM_MANTLES, obj);
    load_cabinet_item((SPIRIT_OBJECTS+"alb"),              NUM_ALBS,    obj);
    load_cabinet_item((SPIRIT_OBJECTS+"certome"),          NUM_TOMES,   obj);
    load_cabinet_item((SPIRIT_OBJECTS+"jointome"),         NUM_JOIN,    obj);
    load_cabinet_item((SPIRIT_OBJECTS+"incense"),          NUM_INCENSE, obj);
    load_cabinet_item((SPIRIT_OBJECTS+"anointing_oil"),    NUM_OILS,    obj);
    load_cabinet_item((SPIRIT_OBJECTS+"ceremonial_drum"),  NUM_DRUMS,   obj);
    load_cabinet_item((SPIRIT_OBJECTS+"ceremonial_bell"),  NUM_BELLS,   obj);
    load_cabinet_item((SPIRIT_OBJECTS+"ceremonial_candle"),NUM_CANDLES, obj);
    load_cabinet_item((SPIRIT_OBJECTS+"chimes"),           NUM_CHIMES,  obj);
    load_cabinet_item((SPIRIT_OBJECTS+"wedtome"),          NUM_WEDB,    obj);
    load_cabinet_item((SPIRIT_OBJECTS+"chalice"),          NUM_CHAL,    obj);
    load_cabinet_item((SPIRIT_OBJECTS+"bread"),            NUM_BREAD,   obj);
    obj->add_prop(CONT_I_CLOSED,1); /* close after loaded */
}
 
void create_receptacle()
{
    set_name("cabinet");
    set_adj("small");
    add_adj("rosewood");
    set_long("This is a small rosewood cabinet. The wood is warm and "+
      "very smooth to the touch. The front legs have been carved in "+
      "the shape of robed figures facing downward with hands "+
      "outstretched to the floor, where the bronze feet rest. "+
      "The feet have been sculpted to depict a huddled group "+
      "looking up at the robed figure. The top of the cabinet "+
      "has an ornate carving upon it in the shape of a pentagram.\n");
    
    add_item("pentagram","Cleverly interwoven within the colors of the wood is a "+
      "following inscription, perhaps you should 'inspect' it more closely.\n");
    add_item("grain","Cleverly interwoven within the colors of the wood is the "+
      "following inscription, written in italic script:\n\n"+
      "I think I have told you, but if I have not, you must have understood, "+
      "that a man who has a vision is not able to use the power of it until "+
      "after he has performed the vision on earth for the people to see... "+
      "It was even then only after the second ceremony, in which I was chosen "+
      "Master Cleric by Psuchae, that I had the power to practice as a full cleric, "+
      "guiding lost souls, and I walked with the power that came through me. "+
      "Of course, it was not I who cured, it was the power from the Spirit "+
      "World, the visions and the ceremonies had only made me like a little "+
      "hole through which the power could come to the Realms.\n\n"+
      "If I thought I was doing it myself, the hole would close up and no "+
      "power could come through.  Then everything I could do would be foolish.\n");
 
    add_prop(CONT_I_WEIGHT,      50000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_VOLUME,      40000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0); /* leave open so can load items */
    add_prop(OBJ_I_NO_GET,1);
    set_alarmv(1.0,0.0,"load_cabinet",({(TO)}));
}
 
int
do_inspect(string str)
{
    notify_fail("Inspect what? the pentagram?\n");
    if (!strlen(str))
        return 0;
    
    if (str != "pentagram" && str != "the pentagram")
        return 0;
    
    write("A five-pointed figure encloses the carving, in the center "+
      "of which are several figures. There is a tall figure, "+
      "adorned in mantle and alb, who lays hands upon another "+
      "that lays prone before him. Behind the figure are two "+
      "kneeling figures in robes, apparently in silent observation. "+
      "The wood has been cut and pieced together so that five "+
      "pieces join at equal angles at the very center of the "+
      "engraving, so that the grain of the wood flows in from "+
      "the edges of the figure to a central point just between "+
      "the tall figure and the prone figure.\n");    
    return 1;
}
 
void
init()
{
    ::init();
    add_action(do_inspect,"inspect");
}