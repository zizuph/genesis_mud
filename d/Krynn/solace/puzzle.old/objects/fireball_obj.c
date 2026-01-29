/* Fireball from sword of fire. ~solace/puzzle/objects/fireball_obj */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

int alarm;
int number_of_cycles;

void create_object()
{
    set_no_show();

    set_name("fireball");
    set_adj("burning");

    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_S_WIZINFO, "A fireball created by a sword of fire.\n");
}

void set_number_of_cycles(int i)
{
    number_of_cycles = i;
}

void start_burning()
{
    E(TO)->add_prop(LIVE_S_SOULEXTRA, "surrounded by a ball of red flame");

    if(!pointerp(get_alarm(alarm)))
        alarm = set_alarm(1.0, 8.0, "burn_enemy");
}

void burn_enemy()
{
    object me = E(TO);
    int dam;

    if(me->query_ghost())
    {
        me->remove_prop(LIVE_S_SOULEXTRA);
        set_alarm(1.0, 0.0, "remove_object");
    }
    else
    {
        switch(random(3))
        {
            case 0:
            {
                me->catch_msg("You scream in agony as your flesh begins "+
                    "to melt.\n");

                tell_room(E(me), QCTNAME(me)+" screams in agony as "+
                    POSSESSIVE(me)+" flesh begins to melt.\n", me);
                break;
            }

            case 1:
            {
                me->catch_msg("Your flesh begins to blacken and char from "+
                    "the intense heat.\n");

                tell_room(E(me), QCTNAME(me)+"'s flesh begins to blacken "+
                    "and char from the intense heat.\n", me);
                break;
            }

            case 2:
            {
                me->catch_msg("Fire plays across your body, burning and "+
                    "scorching away the skin and flesh.\n");

                tell_room(E(me), "Fire plays across "+QTNAME(me)+"'s body, "+
                    "scorching away the skin and flesh.\n", me);
                break;
            }
        }

	dam = random(36) + 15;
	dam -= (dam * me->query_magic_res(OBJ_I_RES_FIRE) / 100);
	if (dam < 0)
	  dam = 0;
        me->heal_hp(-dam); // 15 to 30 hp loss.

        if(me->query_hp() <= 0)          
        {
            me->do_die(me->query_enemy());
            me->remove_prop(LIVE_S_SOULEXTRA);

            set_alarm(1.0, 0.0, "remove_object");
        }
    }

    number_of_cycles--;

    if(!number_of_cycles)
    {
        me->remove_prop(LIVE_S_SOULEXTRA);
        set_alarm(1.0, 0.0, "remove_object");
    }
}
