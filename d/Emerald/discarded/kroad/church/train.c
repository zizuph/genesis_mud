#pragma save_binary

#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit VAMP_LIB_DIR + "train";

#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>

int arch_block();

void create_vamp_room()
{
    set_short("Training room");

    set_long("   This area appears to be a recreational " +
        "area and training facility, apparently installed by some " +
        "long-gone inhabitants of the church.  Various books, guides, and " +
        "training implements can be found about the room.\n" +
        "To the west is a small, dark archway.\n\n");

    add_item(({ "books", "guides" }), "A great number of guides in the " +
        "form of journals, pamphlets, scrolls and books, their subjects vary " +
        "widely...from discussions on hunting to theories on focusing mental " +
        "powers to descriptions of combat techniques.\n");

    add_item(({ "implements", "training implements" }), "A wide array of physical " +
        "training equipment is available and in working condition.\n");

    add_exit("under_church04", "south");
    add_exit("arch",  "west", arch_block);

    set_up_skills();
}

int arch_block()
{
#if 0
    write("Some force prevents you from entering.\n");
    return 1;
#else
    object archroom, *livings;

    archroom = find_object(VAMP_ROOM_DIR + "arch");

    if (archroom && sizeof(livings = FILTER_LIVE(all_inventory(archroom))))
    {
        write("You bump into someone who is already there.\n" +
            "There isn't enough room for you both!\n");
        livings->catch_msg("Someone trying to enter the archway bumps " +
            "into you.\n");
        return 1;
    }

    write("You pass into the blackness of the archway and immediately " +
        "sense powerful magic.\n");

    return 0;
#endif
}

int
select_weapon(string str)
{
    mapping m = ([ "sword"   : SS_WEP_SWORD,
  		   "axe"     : SS_WEP_AXE,
 		   "polearm" : SS_WEP_POLEARM,
          	   "knife"   : SS_WEP_KNIFE,
		   "club"    : SS_WEP_CLUB,
		   "unarmed combat" : SS_UNARM_COMBAT, ]);
    string name;

    if (!strlen(str) ||
        (member_array(str, m_indices(m)) < 0))
    {
        notify_fail("Possible selections are: " + 
            COMPOSITE_WORDS(m_indices(m)) + ".\n");
        return 0;
    }
   
    name = this_player()->query_real_name();

    if (member_array(name, m_indices(chosen_weapon)) >= 0)
    {
        cost_factor[name] += 10;
    }

    chosen_weapon[name] = m[str];

    setuid();
    seteuid(getuid());
    save_map(chosen_weapon, WEAPON_SAVE);

    write("Ok.\n");
    return 1;

}

int sk_no_train(object who)
{
  if (!IS_MEMBER(who) && !EMRLD_WIZ(who))
  {
    command("say Only true vampires may train here!");
    return 1;
  }

/*
  if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
  {
    command("say Sorry " + TP->query_name() + ", but you are " +
        "considered unworthy to train here.");
    return 1;
  }
*/

  return 0;
}

void
init()
{
    ::init();
    init_skill_raise();

    add_action(select_weapon, "select");
}
