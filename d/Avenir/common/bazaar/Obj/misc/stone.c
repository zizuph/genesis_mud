
// In memory.
//    -I.
// The stone adds 80+random (30) mana when you pray before it -
// Can only be done once/session/player

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name(({"stone","rock","memorial","edifice"})); 
    set_pname("stones");
    set_short("stone"); 
    set_pshort("stones");
    set_adj(({"large","standing","marble","rock","solid"}));
    set_no_show_composite(1);  // because the desc. is in the room itself

    set_long("This is a massive standing stone, shaped "+
                   "out of pristine marble and rising "+
                   "upwards like an accusing finger. Carved "+
                   "around the center of the "+
                   "stone are strange symbols and glyphs, "+
                   "surrounding some writing. The "+
                   "edifice seems to emit a strange and sad aura.\n");

   add_item(({"writing","letters","inscription"}),"The writing is etched "+
                   "gently into the rock "+
                   "in thin and flowing characters.\nThey seem "+
                   "to glow with a "+
                   "faint green light.\n");
 
   add_item(({"glyph","glyphs","rune","runes","character",
                   "characters"}),"They "+
                   "surround the writing, carved deeply into "+
                   "the stone. They may be just "+
                   "for decoration, or they may have "+
                   "some deeper meaning.\n");

   add_cmd_item(({"writing","letters","inscription"}),"read",
                   "The inscription reads:\n"+
                   "In Memory of Jebediah\nThe writing glows "+
                   "bright green as you "+
                   "read it.\n");

   add_cmd_item(({"glyph","glyphs","rune","runes",
                   "character","characters"}),"read",
                   "Their meaning is lost on you.\n");

   add_cmd_item(({"stone","rock","memorial","edifice"}),
                   ({"touch","feel"}),"The marble "+
                   "is very smooth to the touch, and feels "+
                   "slightly warmer than the air "+
                   "around.\n");

    add_prop(OBJ_I_LIGHT,0);
    add_prop(OBJ_I_WEIGHT, 1000000); 
    add_prop(OBJ_I_VOLUME, 250000);
    add_prop(OBJ_I_VALUE, 1000); 
    add_prop(MAGIC_AM_MAGIC, ({35, "enchantment"}) ); 
}

void
init()
 {
   ::init();
    add_action("pray_func", "pray");
 }

int
pray_func(string arg)
 {
    string str;

    if(arg == "stone" | arg == "before stone" | arg == "memorial" 
         | arg == "before "+
         "memorial" | arg == "here" | arg == "")
       {
          if (this_player()->query_prop("_i_have_prayed_before_stone_"))
           {
             write(
                "You kneel down and pray before the stone.\n"+
                "The inscription "+
                "glows faintly with a green light.\n"+
                "You rise again.\n");
             say(
                QCTNAME(this_player()) + " kneels down and "+
                "prays before the stone.\nThe inscription "+
                "glows faintly with a green light.\n"+
                QCTNAME(this_player()) + " rises again.\n");
            return 1;
            }
       write("You kneel down and pray before the stone.\n"+
                 "The runes glow bright green for a moment.\n"+
                 "You sense a peace enter your soul, and you mind "+
                 "feels at rest.\nThe runes fade again.\nYou stand up.\n");
       say(QCTNAME(this_player())+" kneels down and prays before "+
                 "the stone.\nThe runes glow bright green "+
                 "for a moment.\nA soft glow seems to enshroud "+
                 this_player()->query_possessive()+" body.\n"+
                 QCTNAME(this_player()) + "  rises again.\n");
       this_player()->add_prop("_i_have_prayed_before_stone_",1);
       this_player()->add_mana(80 + random (30));
   return 1;
     }
 notify_fail("Pray before what ?\n");
 }


