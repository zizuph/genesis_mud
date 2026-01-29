/* Bracers for Jane the Mercenary, Gwyneth, June 1999 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

void
create_armour()
{
    set_name("helmet");
    add_name("helm");
    set_adj("steel-spiked");
    set_short("steel-spiked helm");
    set_pshort("steel-spiked helms");
    set_long("The metal is a high quality steel, perhaps elvish. Sharp spikes stick out from the helm allowing for special tactics during combat for the wearer.\n");

    set_af(this_object());
    set_ac(40);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 700);

    add_prop(OBJ_S_WIZINFO,
        "This armour is worn by Jaine in Kendermore. It has a special " +
        "al though not magical effect. It has spikes that hurts the " +
        "attacker if he hits the wearer on the head.\n");
}

mixed
wear()
{
    object sh;

    setuid();
    seteuid(getuid());

    sh = clone_object(KOBJ + "helm_sh");
    sh->shadow_me(wearer);

    write("You put on the "+short()+".\n");
    say(QCTNAME(wearer) + " puts on the " + short() + ".\n");
    return 1;
}

mixed
remove()
{
    query_worn()->remove_helm_shadow();
    if(wearer)
    {
        wearer->catch_msg("You take off the "+short()+".\n");
        say(QCTNAME(wearer) + " takes off the "+short()+".\n");
    }
    return 1;
}

