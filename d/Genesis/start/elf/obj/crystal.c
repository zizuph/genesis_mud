#include <stdproperties.h>
#include "../stddefs.h"
#include "../tefyma.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;

#define NAT_LONG \
  "It is a tall, standing stone of black crystal, roughly four times as wide " +\
  "as it is thick, and nine times as high. Deep in the blackness beneath its " +\
  "transparent surface is a whirl of glowing sparks, making the rectangular "+\
  "stone look as if it was full of stars.\n" +\
  "Looking at the stars, you hear the ghost of some mighty, majestic music, "+\
  "slowly played by rumbling drums and otherwordly horns, echo in your ears.\n" +\
  "As the music fades away, you notice glowing writing, hidden "+\
  "in between the stars.\n"
  
#define FOR_LONG \
  "It is a tall, standing stone of black crystal, roughly four times as wide " +\
  "as it is thick, and nine times as high.\n"

#define NAMES ({"stone", "crystal"})

#define STAR_ITEM ({"star", "stars", "whirl", "sparks", "light", "lights"})
#define STAR_DESC \
  "The lights are small, coldly glowing points."

#define TEXT_ITEM ({"text", "writing", "glowing writing", "writings"})
#define TEXT_DESC \
  "It reads:\n" +\
    "You are in Faerie. South of here is the Trade Road. Following it " +\
    "south will take you to Green Oaks, the ancestral home of the elves, " +\
    "or north will take you deep into a forest with dangers awaiting the " +\
    "bold explorer. In Green Oaks you will find many things to help " +\
    "you get started. Feel free to explore the surrounding areas. Be " +\
    "careful, when you leave Green Oaks you will encounter enemies that " +\
    "may not look kindly on you. With a little brute strength, you may " +\
    "persuade them otherwise.\n\n" +\
    "Genesis is a huge world. As you travel, explore every little thing " +\
    "you find. Sometimes the greatest surprises can be found in the most " +\
    "unlikely of places. Hints often can be found in descriptions. Other " +\
    "times, you may need to think a little.\n\n" +\
    "You will meet many people. Some will become friends in time, others " +\
    "may become enemies. When you do meet strangers, use 'introduce myself' " +\
    "to them and hopefully they will do the same. If they do, and you want " +\
    "to remember them in the future, simply do 'remember <player name>'. " +\
    "Next time you meet them, you will know them.\n\n" +\
    "If you are in dire circumstances and need wizard intervention, you may " +\
    "'commune all <message>'. Do this only in extreme cases when a bug " +\
    "prevents you from playing the game. If a wizard is available, they " +\
    "will attempt to help out. Type 'help commune' for more information.\n\n" +\
    "To get more general help about Genesis, be sure to look at the help " +\
    "files. Type 'help' or 'help topics' for more information.\n\n" +\
    "If you find bugs or typos that seem to belong to all of Genesis, " +\
    "report them with 'sysbug' or 'systypo'. If you find a bug or a typo " +\
    "in a certain area, these can be reported with 'bug' or 'typo'. Also, " +\
    "if you find something really cool and want to comment on it, use the " +\
    "'syspraise' or 'praise'.\n\n" +\
    "Good luck and welcome to Genesis!\n\n"

#define MUSIC_ITEM ({"music", "drums", "horns", "echo"})
#define MUSIC_DESC \
  "You hear nothing now. It must have been your imagination.\n"

#define BLACK_ITEM ({"blackness", "darkness"})
#define BLACK_DESC \
  "It is a soft darkness, drinking away all light.\n"

#define SURFACE_ITEM ({"surface"})
#define SURFACE_DESC \
  "It is a hard, slick, impermeable surface, transparent to your gaze.\n"

#define GET_FAIL_MSG \
  "It is inseparable from the ground.\n"

#define VOLUME (3 * 12 * 27 LITRES)

create_object() {
  set_name(NAMES);
  set_adj(({"dark", "huge"}));

  set_long(N_KNOW(WRAP(NAT_LONG), WRAP(FOR_LONG)));

  add_item(   STAR_ITEM, WRAP(   STAR_DESC));
  add_item(   TEXT_ITEM, WRAP(   TEXT_DESC));
  add_item(  MUSIC_ITEM, WRAP(  MUSIC_DESC));
  add_item(  BLACK_ITEM, WRAP(  BLACK_DESC));
  add_item(SURFACE_ITEM, WRAP(SURFACE_DESC));

  add_cmd_item(TEXT_ITEM + NAMES, "read", WRAP(TEXT_DESC));

  add_prop(OBJ_I_VOLUME,            VOLUME);
  add_prop(OBJ_I_WEIGHT, GLASS_DENS(VOLUME));
  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
}



string native_knowledge(string native, string foreign) 
{
  if (this_player() && IS_NATIVE(this_player()))
    return native;
  else
    return foreign;
}
