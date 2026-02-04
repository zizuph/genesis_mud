/* A manege room. Mortricia 920927 */
/* Modifications
 *   - Fixed it so that one cannot die on the juggling quest
 *     Petros, May 2009
 */
 
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"

object check_short(string sh_desc, object ob);
object check_sh(string sh_desc, object ob);

init()
{
    add_action("do_juggle", "juggle");
    ::init();
}

void
create_room()
{
    set_short("Manege");
    set_long(BSN(
        "You are standing on the manege. " +
        "The audience wonder what you are doing there, since " +
        "they cannot figure out, and neither can you, what kind " +
        "of performer you are."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "behind1", "southeast", 0);
}

do_juggle(string what)
{
    int i, j_val, drunk;
    object ob1, ob2, ob3, ring, violets;
    string str1, str2, str3;

    if (!what) {
        write("Juggle with what?\n");
        return 1;
    }
    if (sscanf(what, "with %s", str2) != 1) {
        write("Juggle with what?\n");
        return 1;
    }
    if (str2 != "balls" && str2 != "cones") {
        write("Juggle with what?\n");
        return 1;
    }
    if (str2 == "balls") str1 = "ball";
    if (str2 == "cones") str1 = "cone";
    i = 0;
    if(ob1=check_sh("red "+str1, TP)) i++;
    if(ob2=check_sh("blue "+str1, TP)) i++;
    if(ob3=check_sh("green "+str1, TP)) i++;
    if(i==0) {
        write("You have no "+str2+" to juggle with!\n");
        return 1;
    }
    if(i==1) str3 = "one " + str1;
    if(i==2) str3 = "two " + str2;
    if(i==3) str3 = "three " + str2;

    j_val = 0;
    ring = check_short("iron ring", TP);
    if (ring) {
        j_val = ring->query_prop(str1+"_juggling");
    }
    // Adding a hp check so that the rotten tomatoes won't
    // kill the questor.
    if (TP->query_hp() <= (40 - j_val * 10))
    {
        write("You are too hurt at the moment to be effective "
            + "at juggling in front of others!\n");
        return 1;
    }

    write("You start to juggle with "+str3+".\n");
    say(QCTNAME(TP)+" starts to juggle with "+str3+".\n");

    drunk = TP->query_intoxicated() > 3;
    if (i<3 || j_val<4 || drunk) {
        write(BSN(
            "You drop some of the " + str2 + ". " +
            "The audience whistles disparaging. You better leave."
            )); 
        say(QCTNAME(TP) + " fumbles and drop the " +
                        str2 + "! What a jerk!\n");
        if (drunk) write("Maybe you are too drunk?\n");
        if (j_val<4) write("Maybe you should practise first?\n");
        if (i<3) write("You better use three "+str2+" next time!\n");
        if(ob1) ob1->move(TO);
        if(ob2) ob2->move(TO);
        if(ob3) ob3->move(TO);
        write("Oops! They throw rotten tomatoes at you!\n");
        write(BSN(
            "As you get hit you realise that some of the " +
            "tomatoes really aren't tomatoes but stones!"
            ));
        TP -> reduce_hit_point(40 - j_val*10);
    } else {
        violets = check_short("bouquet of violets", TP);
        if (!violets) {
            write(BSN(
            "What a performance! The audience worship you, " +
            "and someone throws a bouquet of flowers, which " +
            "you catch without dropping any "+str2+"."
            ));
            violets = clone_object(TENT_DIR + "violets");
            violets -> add_prop("q_solver", TP->query_name());
            violets -> move(TP);
        } else {
            write(BSN(
            "What a performance! The audience worship you."
            ));
        }
        say(QCTNAME(TP)+" juggles like a real juggler!\n");
    }
    return 1;
}

object
check_short(string sh_desc, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_short() == sh_desc &&
            ob_arr[i]->query_prop("q_solver") == ob->query_name()) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}

object
check_sh(string sh_desc, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_short() == sh_desc) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}
