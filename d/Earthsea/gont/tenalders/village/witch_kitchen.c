/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's kitchen
 * contains an adventurer's type skill training center
 * with herbalism and small magic and alchemy skills
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <ss_types.h>

private object witch;

public void
set_up_skills()
{
    sk_add_train(SS_SNEAK, "sneak into rooms", "sneak", 100, 20);
    sk_add_train(SS_HIDE, "hide things", "hide", 100, 20);
    sk_add_train(SS_AWARENESS, "find things", "awareness", 100, 30);
    sk_add_train(SS_LANGUAGE, "understand other languages",
        "language", 100, 30);
    sk_add_train(SS_SPELLCRAFT, "understand and use magic",
        "spellcraft", 100, 20);
    sk_add_train(SS_HERBALISM, "identify and use herbs", 
        "herbalism", 100, 20);
    sk_add_train(SS_DEFENCE, "defend oneself in combat",
        "defence", 100, 20);
    sk_add_train(SS_ALCHEMY, "identify and mix potions",
        "alchemy", 100, 20);
    sk_add_train(SS_ELEMENT_EARTH,"apply earth magic",
        "earth magic", 100, 20);
    sk_add_train(SS_ELEMENT_AIR, "apply air magic", 
        "air magic", 100, 20);
    sk_add_train(SS_ELEMENT_FIRE, "apply fire magic", 
        "fire magic", 100, 20);
    sk_add_train(SS_ELEMENT_WATER, "apply water magic",
        "water magic", 100, 20);
    sk_add_train(SS_ELEMENT_LIFE, "apply life magic", 
        "life magic", 100, 20);
    sk_add_train(SS_OPEN_LOCK, "open locks without key", "open locks",
        100, 20);
    sk_add_train(SS_FR_TRAP, "find and remove traps",
        "find and remove traps", 100, 20);
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed",
        "unarmed combat", 100, 30);
    sk_add_train(SS_CLIMB, "climb", "climb", 100, 30);
}

public void
create_earthsea_room()
{
    set_short("The witch's kitchen");
    set_long("This is a room full of interesting smells and " +
        "aromas. There is a tall hearth that takes up the " +
        "major portion of the west wall, and a large black " +
        "kettle, simmering merrily, hangs on the hob over " +
        "a low fire. A long wooden counter or work table " +
        "runs along the north wall under an open " +
        "window. The counter is populated with alembics, " +
        "tubes, vials, mortars with pestles, and various " +
        "alchemical paraphernalia. A broom stands in the " +
        "corner. You may find that you are able to <improve> or " +
        "<learn> new skills here.\n");
    add_item((({"smells", "aromas"})),
        "The scent of herbs, cooking and unusual chemical " +
        "mixtures tickles your nose.\n");
    add_item((({"kettle", "large black kettle", "black kettle"})),
        "The kettle on the hob could be cooking dinner... " +
        "or perhaps something more interesting. Whatever " +
        "it is doesn't feel evil here though.\n");
    add_item("window",
        "The window opens on a garden, where you see " +
        "all sorts of growing things.\n");
    add_item((({"table", "counter"})),
        "The sturdy table of hard oak is stained where " +
        "chemicals and potions have spilled on it.\n");
    add_item((({"alembics", "alembic"})),
        "The alembic is a glass apparatus with " +
        "two beakers connected by a long tube. Under one " +
        "beaker a small fire is burning.\n");
    add_item((({"tubes","vials","mortars with pestles",
        "paraphernalia", "alchemical paraphernalia"})),
        "The sight of this equipment dispells all doubt: " +
        "This is definitely the home of a witch.\n");
    add_item((({"fire", "hearth", "hob"})),
        "The hob is a black metal arm that supports " +
        "the kettle over the low fire in the hearth.\n");
    add_item("broom", "It is the witch's broom.\n");
    add_prop(ROOM_I_INSIDE, 1);
    create_skill_raise();
    set_up_skills();
    reset_room();
    add_exit("witch_entry", "southeast");
    add_exit("witch_living_room", "south");
}

public void
reset_room()
{
    if(!objectp(witch))
    {
        witch = clone_object("/d/Earthsea/gont/tenalders/npc/herb_witch");
        witch->move(this_object());
        witch->command("emote enters mysteriously.");
    }
}

public void
init()
{
    ::init();
    init_skill_raise();
    call_other("/d/Earthsea/gont/tenalders/village/witch_roof",
        "load_me");
    call_other("/d/Earthsea/gont/tenalders/village/witch_garden_3",
        "load_me");
}
