// -*-C++-*-
// Ilyian (September 24), mostly copied from Kazz's
//                 lichen poison.
// last update:
// purpose:        Poison for Jadestone's dagger.
// note:
// bug(s):
// to-do:


#include <poison_types.h>
#include <macros.h>
#include "/d/Avenir/common/common.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);
#define DEATH_LOG	"/d/Avenir/log/bazaar/poison_death"
#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))

inherit "/std/poison_effect";

void
create_poison_effect()
{
  set_name ("amarik_sons");
  add_name("_jp_id");
  set_interval(30);
  set_time(1800);
  add_prop(OBJ_M_NO_DROP,"Drop what?");
  set_strength(100);
  set_damage(({POISON_HP,240, POISON_STAT, SS_CON, POISON_USER_DEF,1}));
  set_poison_type("standard");
  set_silent(1);
}


void
special_damage (int damage)
{
    int msg_num = random(7);

    if (!objectp(poisonee))
	return;

    int res = poisonee->query_magic_res(MAGIC_I_RES_POISON);
    if (random(100) < res)
    {
        return;
    }

    // player and room tells
    switch (msg_num)
        {
          case 0:
            poisonee->catch_msg ("You suddenly feel very dizzy.\n");
            TR(QCTNAME(poisonee) + " holds " + POSSESS(poisonee) +
                " hands to "+ POSSESS(poisonee) + " head.\n");
            break;
          case 1:
            poisonee->catch_msg (
                "Your blood turns to ice and you feel a rush "
                      +"of irrational terror.\n" );
            TR(QCTNAME(poisonee) + "'s face goes pale.\n");
            poisonee->add_panic(200);
            break;
          case 2:
            poisonee->catch_msg ("All the feeling goes out of your "
                      +"arms.\n" );
            poisonee->add_fatigue(-50);
            break;
          case 3:
            poisonee->catch_msg (
                            "A violent shudder runs down your spine.\n");
            TR(QCTNAME(poisonee) + " shudders violently.\n");
            break;
          case 4:
            poisonee->catch_msg ("Your stomach throbs with unbearable "
                             +"pain.\n");
            TR(QCTNAME(poisonee) +
               " grabs " + POSSESS(poisonee) + " stomach.\n");
            poisonee->command("$moan softly");
            break;
          case 5:
            poisonee->catch_msg ("You start to shake with uncontrollable "
                        +"fear.\n");
            TR(QCTNAME(poisonee) + " begins to shake severely.\n");
            poisonee->catch_msg("You feel the need to flee!\n");
            poisonee->run_away();    // Run 4 rooms away.
            poisonee->run_away();
            poisonee->run_away();
            poisonee->run_away();
            break;
          case 6:
            poisonee->catch_msg (
                            "You suddenly cannot catch your breath.\n");
            TR(QCTNAME(poisonee) +
                " gasps and clutches " + POSSESS(poisonee) + " throat.\n");
            poisonee->add_mana(-80);
            break;

          default:
            poisonee->catch_msg ( "You feel violently ill.\n");
            break;
        }

}

void
timeout()
{
  poisonee->catch_msg("Your blood feels clean again.\n");
  ::timeout();
}

void
reconfig_me(int newstr)
{
  set_damage(({POISON_HP, newstr, POISON_STAT, SS_CON,
               POISON_USER_DEF,1}));
}

kill_player()
{
   write_file(DEATH_LOG, ENV(TO)->query_name()
            + "("+ENV(TO)->query_average_stat()
            + ") dies from cinquenda poison on "+ctime(time())+" "
            + " at "+file_name(ENV(ENV(TO))) + ".\n");
   ::kill_player();
}
