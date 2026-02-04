/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

object lib;

public void
reset_room()
{
    if (lib) return;
    
    seteuid(getuid());
    lib = clone_object(GUILD_DIR + "librarian");
    lib->move_living("north", this_object());
}

public void
create_room()
{
    object door;

    set_short("The Mystic Library");
    set_long("Ancient tomes line countless shelves, that reach " +
             "back into racks. The chamber is lit with candles that " +
             "have crystal cases, hung like lamps. In the center of the " +
             "room is a round mahogany table, upon which is a ledger. " +
             "A tall rack stands against the north wall. The air is dry " +
             "and an absolute silence is kept here.\n");

   add_my_desc("A set of wooden stairs leads up to a loft.\n");

   door = clone_object(GUILD_DIR + "office/od1");
   door->move(this_object());
   door->set_key(9832);
   
   add_exit(GUILD_DIR + "guild",    "east",     0);
   add_exit(GUILD_DIR + "arcane",   "arcane",   "@@my_guild");
   add_exit(GUILD_DIR + "chancery", "west",     "@@my_order");
   add_exit(GUILD_DIR + "study",    "up",       "@@my_order");
   add_exit(GUILD_DIR + "lang_sec", "language", "@@my_guild");
   add_exit(GUILD_DIR + "achamber", "archives", "@@my_guild");
   
   add_item(({"candle", "cases", "case", "lamp"}),
            "Bright white candles housed in small crystal cases. " +
            "They are hung from the ceiling on silver chains.\n");
   add_item("table", "A large mahogany table, it is round and has " +
                     "a smooth flawless surface.\n");
   add_item("rack", "It is a large rack set into the north wall. " +
                    "It holds scrolls and parchments.\n");
   add_item("scrolls", "These are ancients scrolls housed in the racks.\n");
   add_item("parchments", "They contains ancient handwritings.\n");
   add_item("ledger", "It is an ancient tome, the cover bears the " +
                      "emblem of a silver star in a white circle.\n");
   add_cmd_item("ledger", "read",
      "Our might is wisdom, our way is truth. Seek only that which " +
      "is holy and far shall ye rise. Many are the mystic powers " +
      "that ye shall gain with us. Let the Ancients be your guides, " +
      "for in them reside all knowledge.\n\n" +
      "Before you join our sacred Order, let it be known that many " +
      "of our ways might seem incompatible with the world. This is " +
      "due to the fact that we are not entirely of the world. Thus " +
      "shall ye be restricted in thy arms, taking only those prepared " +
      "for thee here in our shrine. Thou shalt be expected to uphold all " +
      "that is holy and truth. Charity and peace are virtues that must " +
      "abide in the hearts of all mystics, but greater still is the role " +
      "of mystery. Mystery binds us together in solemnity, for it is " +
      "this virtue to which we owe our very foundation.\n");
   reset_room();
}

public int
my_order()
{
   if (!MEMBER(this_player())) {
       write("Only those with mystic wisdom may enter there.\n");
       return 1;
   }
   return 0;
}

public int
my_guild()
{
   if (!MEMBER(this_player())) {
       write("Only members of the Order may enter there.\n");
       return 1;
   }
   write("You move deep into the library.\n");
   return 0;
}

public int
is_closed()
{
    if (lib)
        lib->command("say I'm sorry, the archives are closed now.");
    return 1;
}
