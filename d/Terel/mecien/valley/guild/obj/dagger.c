/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <poison_types.h>
#include <comb_mag.h>

void set_poison(object ob);
int query_poison();

object poison;
int has_poison;

void
create_weapon()
{
    set_name("dagger");
    set_long("@@long_desc");
    set_adj("arcane");
   add_name("arcane_dagger");
    set_short("arcane dagger");

    set_hit(18);
    set_pen(16);
    set_wt(W_KNIFE);

    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, 350);
    add_prop("mystic_weapon", 1);
    add_prop("poison_holder", 1);
    add_prop(MAGIC_AM_MAGIC, ({5, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This dagger is magic.\n", 1,
	       "It can hold mystic poison.\n", 10}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    
    has_poison = 0;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() +
           "#n_po#" + query_prop("poison_no_times") + "#";
}

void
init_recover(string arg)
{
    int no_times;
    string foobar;

    init_wep_recover(arg);
    sscanf(arg, "%s#n_po#%d#%s", foobar, no_times, foobar);
    if (no_times > 0) add_prop("poison_no_times", no_times);
}

string
long_desc()
{
    string str;

    str = "This ornate silvery dagger is inscribed with mystic symbols "+
          "and strange rune characters. The pommel takes the shape " +
          "of a writhing serpent.";
    if (has_poison)
        str += " You perceive a sheen of liquid on the blade.";
    if (query_prop("poison_no_times") > 6)
        str += " The blade looks dirty, you better let Eringil clean it.";

    return break_string(str + "\n", 72);
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit);
    if (NPMATTACK(enemy)) return 0;
    if (has_poison && !random(4) && poison) {
        poison->move(enemy);
        poison->start_poison();
        has_poison = 0;
    }
    return 0;
}

void
set_poison(object ob)
{
    if (has_poison) return;
    poison = ob;
    if (poison) has_poison = 1;
}

int query_poison() { return has_poison; }
