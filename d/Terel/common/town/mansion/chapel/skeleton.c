/* A skeleton. Mortricia 920910 */

inherit "/std/monster";
inherit "/std/act/seqaction";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define TP          this_player()
#define TO          this_object()
#define ETO         environment(TO)

int has_skull, has_ring;
object ring;

public void
update_skeleton()
{
    has_skull = 0;
    has_ring = 1;

    if (present("ring")) return;
    seteuid(getuid());
    ring = clone_object(MANSION + "chapel/ring");
    ring->move(TO);
}

public void
create_monster()
{
    set_name("skeleton");
    set_short("bony skeleton");
    set_long("@@my_long@@");
    set_adj("bony");

    set_race_name("skeleton");
    set_gender(2);

    set_stats(({ 1, 1, 1, 1, 1, 1}));
    set_hp(9999);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 1000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_item(({"bone", "bones"}), "@@bone_desc");
    add_item(({"head", "skull"}), "@@skull_desc");

    set_all_hitloc_unarmed(1);
    set_all_attack_unarmed(1, 1);

    update_skeleton();
}

public string
my_long()
{
    string str;

    if (has_skull == 1) {
        str = "A complete skeleton of an adult human. This poor " +
              "individual probably got trapped in this room.\n";
    } else {
        str =
        "A skeleton of an adult human. As far as you can tell all " +
        "bones are intact, though somewhat burned, except that its " +
        "skull is missing. This poor individual probably got trapped " +
        "in this room, and " +
        "the same might happen to you if you aren't careful.\n";
    }
    return str;
}

public string
bone_desc()
{
    string str;

    if (has_ring) {
        str = "The burned bones are covered with dust and cobwebs. " +
              "Something glitters behind them.\n";
    } else {
        str = "The burned bones are covered with dust and cobwebs.\n";
    }
    return str;
}

public string
skull_desc()
{
    string str;

    if (has_skull == 1) {
        str = "It's a skull, with two empty holes.\n";
    } else {
        str = "Yes, the skull is missing. " +
              "Maybe you should try to find it?\n";
    }
    return str;
}

public void
my_point(object me)
{
    if (me && environment(me) == ETO) {
        tell_object(me, "The skeleton seems complete now.\n");
        tell_object(me, "It gives you something.\n");
        tell_object(me,
            "You also hear a ghostly female voice in your head asking " +
            "you to find her grandchild and deliver " +
            "her most precious object.\n");
    }
}

public void
drop_item(object item, object from)
{
    if (item == present("skull")) {
        command("drop skull");
        if (from && environment(from) == ETO)
            from->catch_msg("The skull probably didn't fit.\n");
    } else if (item) {
        tell_room(ETO, "The " + item->short() + " just falls off " +
                  QTNAME(TO) + ".\n");
        item->move(ETO);
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (ob == ring) return;
    
    if (ob->query_prop("_skull_finder") == from->query_name() && has_skull == 0) {
        ob->remove_object();
        has_skull = 1;
        if (has_ring) {
            ring->add_prop("_skull_finder", from->query_name());
            ring->move(TP);
            set_alarm(2.0, -1.0, &my_point(from));
            has_ring = 0;
        }
        return;
    }
    set_alarm(2.0, -1.0, &drop_item(ob, from));
}
