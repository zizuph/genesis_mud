/*
 * Name:	    airwall
 *
 * Object:	    /d/Shire/rogon/sdir/bl/airwall.c
 *
 * Cost:	    10 mana.
 *
 * Skills:	    Spellcraft, conjuration, air.
 *
 * Description:     Creates a wall of dense churning air between two rooms.
 *
 * Requirements:    Level 1 spell.
 *
 */

#include "defs.h"

#inherit SPELL_FILE;

string dir_to;
string dir_from;
object this_room;
object other_room;

create_spellobj()
{
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_AIR, 10);
    set_spell_name("airwall");
    set_classes(([1:1, 10:11]));
    set_desc("Creates a dense charging wall of air between two rooms.");
    set_syntax("[to the] <direction>");
}

object *
area_of_effect(string arg)
{
    mixed ret;
    string *dir;

    notify_fail(
	"Syntax: "+query_spell_name()+" <class> to the <direction>\n"+
	"        "+query_spell_name()+" to the <direction>\n"+
	"        "+query_spell_name()+" <class> <direction>\n"+
	"        "+query_spell_name()+" <direction>\n\n"+
	"Note that the class of the spell should be from 1 to 5,\n"+
	"or true for the 'True'-spells.\n" );

    if (!arg)
	return 0;

    ret = parse_between_rooms(arg, dir);

    if (intp(ret))
	switch (ret)
	{
	    case 0: return notify_fail("You must specify a direction.\n");
	    case 1: return notify_fail("That is not an obvious exit.\n");
	    case 2: return notify_fail("Your spell fails.\n");
	    case 3: return notify_fail("Your spell fails.\n");
	    default: return 0;
	}

    if (member_array(dir[0], ({
	"north", "south", "east", "west",
	"northeast", "northwest", "southeast", "southwest" })) == -1)
	return notify_fail("Only horizontal exits are allowed.\n");

    str_to = dir[0];
    str_from = dir[1];

    this_room = ret[0];
    other_room = ret[1];

    return ret;
}


do_instant_effect(object *targets, int result)
{
    object wall;

    if (RNMAGIC(this_room) || RNMAGIC(other_room))
	return;

    setuid();
    seteuid(getuid());

    wall = clone_object(THIS_DIR + "wallair");
    wall ->init_wall(this_room, str_to, other_room, 1);

    wall = clone_object(THIS_DIR + "wallair");
    wall ->init_wall(other_room, str_to, this_room, 0);

    return 1;
}
