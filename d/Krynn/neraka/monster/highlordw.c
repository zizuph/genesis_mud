/* The dragon highlord, pretty nasty once he's awake :)
   This is the awake version, too, so watch out! */

/* Navarre 2007 Feb. Changing name, he can't be ariakas, because
   Ariakas is already in Sanction.
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include QUESTH

inherit M_FILE

int num, untied;

object
go_to_sleep()
{
    object new_highlord;
    seteuid(getuid(TO));
    command("emote yawns and stretches his body.");
    command("emote lies down to sleep!");
    command("snore");
    new_highlord = clone_object(MON + "highlord");
    new_highlord->move(E(TO));
    set_alarm(0.1,0.0,"remove_object");
    return new_highlord;
}

void
reset_monster()
{
    num = 0;
    untied = 0;
    add_item("key", "It's a small bronze key. It's secured to the belt.\n");
}

void
create_krynn_monster()
{
    int i;
    set_name("highlord");
//    add_name("ariakas");
    set_long("You can't see much about this person since he's covered with " +
	     "dragonscale armour and wears a mask. He is sitting at the " +
	     "table with his back turned to you, apparently writing " +
	     "something. He must be very sure of himself being in this " +
	     "room without any guards. You feel it's better to leave him " +
	     "alone right now.\n");

    add_item(({"dragon scale", "dragon scale armour", "scale armour"}),
	     "It is real dragon scale armour, not a cheap imitation. It's " +
	     "all held together with a black belt.\n");
    add_item("mask",
	     "A very ugly mask, it hides most of the face. You can't see " +
	     "who it is or what it is under it.\n");
    add_item(({"belt", "black belt"}), "@@belt");
    add_item("key", "It's a small bronze key. It's secured to the belt.\n");

    add_cmd_item("key", ({"get", "take"}), ({"@@try_get", "@@try_get"}));
    add_cmd_item(({"dragon scale", "dragon scale armour", "scale armour",
		     "mask", "belt"}), "get",
		 "You can't get it since the highlord is wearing it!\n");
    add_cmd_item("belt", ({"untie", "unbuckle", "open", "cut"}),
		 ({"@@untie", "@@untie", "@@untie", "@@cut"}));

    set_race_name("human");
    set_short("male dragon highlord");
    set_adj("dragon");

    for (i = 0; i < 6; i++)
      set_base_stat(i, 150 + random(50));
    
    set_alignment(-900);
    set_knight_prestige(3000);

    set_all_attack_unarmed(150, 150);
    set_all_hitloc_unarmed(150);

    NEVERKNOWN;
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);


    enable_reset();
}

void
init_living() 
{ 
    ADA("kill"); 
}

int
kill(string str)
{
    if (!id(str))
	return 0;
    write("As you prepare yourself for the kill you feel a great force " +
	  "lifting you out of the room. Now you understand why the highlord " +
	  "can sit in his room without any guards around, the room is filled " +
	  "with anti violence magic.\n");
    say(QCTNAME(TP) + " tries an attack but was carried out of the room.\n");
    TP->move_living("south", TDIR + "city11", 1);
    return 1;
}

string
try_get()
{
    object key;
    string str;
    
    str = query_item_rest_command();
    
    if (str != "from belt")
      return "From where do you want to take the key?\n";
    
    write("You don't even get as far as reaching the belt.\n" +
	  "The highlord turns around to you and a bolt of lightning " +
	  "strikes from his hands and burns you extremely badly!\n");
    TP->heal_hp(-200);
    TP->do_die(TO);
    return "";
}

string
belt()
{

    if (num > 0)
      return "It's a fine black leather belt.\n";
    return "It's a fine black leather belt with a golden buckle. " +
      "Your eyes are drawn to the key hanging in the belt.\n";
}

string
untie()
{
    if (untied > 0)
      return "The belt is already untied.\n";

       write("You don't even get as far as reaching the belt.\n" +
	  "The highlord turns around to you and a bolt of lightning " +
	  "strikes from his hands and burns you extremely badly!\n");
    TP->heal_hp(-800);
    TP->do_die();
    return "";
}

string
cut()
{
    if (untied > 0)
      return "The belt is already untied, no need to cut it.\n";
    if (!present("weapon", TP))
      return "You have no sharp weapon to cut the belt with.\n";
    write("You don't even get as far as reaching the belt.\n" +
	  "The highlord turns around to you and a bolt of lightning " +
	  "strikes from his hands and burns you extremely badly!\n");
    TP->heal_hp(-800);
    TP->do_die();
    return "";
}

public int
is_awake()
{
  return 1;
}

