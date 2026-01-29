/*
 * A poisoned dagger
 *
 * !!! OBSOLETE !!!
 *
 * PLEASE DO NOT USE THIS CODE!
 * USE /d/Gondor/common/wep/poison_dagger.c INSTEAD
 * Where this file is used, please replace it!
 * Olorin, 26-oct-1994
 */
inherit "/std/weapon";
#include <ss_types.h>
#include <wa_types.h>
#include <poison_types.h>
#include <macros.h>

int poison_used;

create_weapon()
{

/* Set up the name of the dagger, etc. */

    set_name("dagger");
    set_short("sharp dagger"); /* Observe, not 'a small dagger' */
    set_long("@@long_desc");  /* This is VBFC to tell of the poison on the */
                            /* dagger. */
    set_adj("steel");
    set_adj("short");

/* Make it fairly ordinary */
    set_hit(12);
    set_pen(10);
    set_wt(W_KNIFE);

    set_dt(W_IMPALE);
    set_hands(W_ANYH);

/* the poison isn't used, upon creation */
    poison_used = 0;

}

string
long_desc()
{
    if(poison_used)
        return "You see nothing special about the dagger.\n"; 
    else
        return "You percieve a sheen of liquid on the blade.\n"; 
}

/*
 * We redefine did_hit() in order to actually poison the player.  We will
 * set it up so that the poison wears off the blade after a while.
 */

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int
phit)
{
    object poison;
    seteuid(getuid(this_object()));
    if (phurt <=0) return 0;
    if(!poison_used) {
        poison = clone_object("/std/poison_effect");
        if(poison) {
            if(random(2))
                poison_used = 1;
            log_file("curses",enemy->query_name()+" was poisoned by a poisoned dagger, by "
              + query_wielded()->query_name()+" on "+ctime(time())+".\n");
            poison->move(enemy);
            poison->set_time(2000);            /* Nice and long */
            poison->set_interval(24);
            poison->set_strength(40);
            poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_STR}));
            poison->start_poison();
            tell_object(query_wielded(),
              "You stab your opponent in the "+hdesc+", and make sure the poison\n"+
              "enters the wound!\n");
            return 0;
        }
        else 
            write("Failed to load poison for some reason.\n"); 
    }
    return 0;
}

query_recover()
{
  return MASTER + ":" + query_wep_recover() + "#p_u#" + poison_used + "#";
}

init_recover(arg)
{
  string dummy;
  init_wep_recover(arg);
  sscanf(arg, "%s#p_u#%d#%s", dummy, poison_used, dummy);
}
