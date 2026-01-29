inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

#define STD_HIT 20
#define STD_PEN 20
#define TO      this_object()
#define TP      this_player()
#define ETO     environment(TO)

public void
create_weapon()
{
    set_name("dagger");
    set_adj("black");
    set_short("black dagger");
    set_long("A sharp black iron dagger.\n");
    set_hit(STD_HIT);
    set_pen(STD_PEN);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
}

/* set_wf() is set from cwraith.c, since I suspect that this dagger
  is used elsewhere too. Mortricia */
public mixed
wield(object obj)
{
    if (interactive(ETO) || interactive(TP)) {
        set_alarm(1.0, -1.0, &remove_object());
        return "The " + short() + " disintegrates.\n";
    }
    return 0;
}
