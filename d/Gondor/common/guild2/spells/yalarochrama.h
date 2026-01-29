/*
 * /d/Gondor/common/guild2/spells/yalarochrama.h
 *
 * A spell for the Morgul Mages to summon a winged steed.
 * yala - roch - rama = summon steed (horse) winged
 * 
 * Class 4 summoning spell
 * Element Air; Form Conjuration
 * Area of effect: object
 *
 * Ingredient: snake skin, gem
 * Mana: 100, 50 on failure
 * Skills: SS_ELEMENT_AIR, SS_FORM_CONJURATION, SS_SPELLCRAFT
 * Description: Summons /d/Gondor/common/guild2/npc/steed.c
 * Requirements: Morgul Mage, nazgul only
 *               mage robe must be present
 *
 * Olorin, 09-jan-1995
 */

#pragma strict_types

#include "/d/Avenir/include/steed.h"

#define MS_YALAR_INGR     ({ "snake skin", "_gem_ingredient", })
#define MS_YALAR_MANA	   100
#define MS_YALAR_MANA_FAIL  50
#define MS_YALAR_TASK     TASK_ROUTINE
#define MS_YALAR_LIST     ({ SS_ELEMENT_AIR, SS_FORM_CONJURATION, SS_SPELLCRAFT})
// The room in which the steed hides when it is supposed to be flying
#define STEED_ROOM	(MORGUL_SPELL_OBJS + "steed_room")


void
land_announce(object mage, object steed, int i)
{
    switch (i)
    {
    case 1:
        tell_room(ENV(mage), "A dark shape, like a cloud and yet not like " +
            "a cloud, for it moves far too quickly, is coming out of the " +
            "sky, speeding towards you, blocking out all light as it " +
            "approaches.");
        set_alarm(5.0, 0.0, &land_announce(mage, steed, 2));
        break;

    case 2:
    default:
        tell_room(ENV(mage), "Blind fear and deadly cold embrace you as " +
            "the dark shape draws nearer.");
        return;
        break;
    }
}

void
move_steed(object mage, object steed)
{
    object  room = ENV(mage);

    if ((!room->query_prop(ROOM_I_IS)) ||
        ( room->query_prop(ROOM_I_INSIDE) && (file_name(room) != AVENIR_PORT_PATH)) ||
        ( room->query_prop(MORGUL_I_NO_SUMMON_STEED)) ||
        ( room->query_prop(ROOM_M_NO_TELEPORT)))
    {
        tell_object(mage, "Your winged steed tries to follow your " +
            "summons but is unable to reach you!\n");
        tell_room(ENV(steed), "The winged beast stretches its pinions " +
            "and flies off into the sky.\n", steed);
        steed->remove_object();
        return;
    }
    steed->move_living("M", room);
    tell_room(room,
        "A huge winged beast descends from the sky and lands here.\n",
        ({ steed, mage }) );
    tell_object(mage,
        "Your winged steed descends from the sky and lands here.\n");
}

mixed
do_yalarochrama(string str)
{
    object  tp = this_player(),
           *ingr_arr,
            room = ENV(tp),
            steed;
    string  fail,
            msg;
    int     is_wiz = tp->query_wiz_level(),
            result,
            delay;

#if DEBUG
    is_wiz = 0;
#endif

    if (strlen(str))
        return "You cannot summon "+str+"!\n";

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()))
        return "You cannot cast this spell during a fight!\n";
    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    if (!room->query_prop(ROOM_I_IS) || 
	(room->query_prop(ROOM_I_INSIDE) && 
	 (file_name(room) != AVENIR_PORT_PATH)))
        return "You cannot summon your winged steed here!\n";

    if (room->query_prop(MORGUL_I_NO_SUMMON_STEED))
        return "A power greater than the Dark Lords prevents you from summoning your steed here!\n";

    if (room->query_prop(ROOM_M_NO_TELEPORT))
        return "A power greater than the Dark Lords prevents you from summoning your steed here!\n";

    ingr_arr = find_ingr(MS_YALAR_INGR, tp);

    if (stringp(fail = check_player(tp,
        MS_YALAR_INGR, MS_YALAR_MANA, MS_YALAR_MIN)))
        return fail;

    // those bloody wizards always have an advantage.
    if ((!(is_wiz)) && ((result =
        (tp->resolve_task(MS_YALAR_TASK, MS_YALAR_LIST))) <= 0))
    {
#if DEBUG
    write("DEBUG: yalarochrama fail result: " + result + "\n");
#endif
        tp->add_mana(-(MS_YALAR_MANA_FAIL));
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: yalarochrama result: " + result + "\n");
#endif

    say(QCTNAME(TP) + " begins to chant in a horrible, rasping speech and " +
        "gazes far into the distant sky.\n" + CAP(PRONOUN(tp)) + " lifts " +
        POSSESSIVE(tp) + " arms to the sky and begins a keening wail, as " +
        "if calling to something.\nFar off, storm clouds break, and a " +
        "distant figure appears in the sky.\n");
    write("Using the power the Dark Lord has bestowed upon you, you summon " +
        "your winged steed with a horrible chant, wailing the words " +
        "\"Yala roch rama\" over and over again. Far off, storm clouds " +
        "break, and a distant figure appears in the sky.");

    if (!is_wiz)
    {
        tp->add_mana(-(MS_YALAR_MANA));
        remove_ingr(ingr_arr);
    }

    seteuid(getuid());
    steed = tp->query_prop(MORGUL_O_STEED);
    if (!objectp(steed))
    {
        steed = clone_object(MORGUL_NPC + "steed");
        steed->set_owner(tp);
        tp->add_prop(MORGUL_O_STEED, steed);
    }

    delay = 20 + random(40);
    set_alarm(itof(delay - 10), 0.0, &land_announce(tp, steed, 1));
    set_alarm(itof(delay), 0.0, &move_steed(tp, steed));

    if ((room = ENV(steed))->query_prop(ROOM_I_IS))
    {
        tell_room(room, "The winged beast stretches its pinions and " +
            "flies off into the sky.\n", steed);
        steed->move_living("M", STEED_ROOM);
    }

    return 1;
}
