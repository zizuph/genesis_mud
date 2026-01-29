/* Standard newbie weapon. ~mucalytic/std/newbie_weapon */

inherit "/std/weapon";

#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "../master_defs.h"
#include "/sys/stdproperties.h"

int destroy_alarm;

public void create_newbie_weapon()
{
}

nomask void create_weapon()
{
    set_hit(3);
    set_pen(3);

    add_prop(OBJ_M_NO_SELL, "You cannot sell this object!");
    add_prop(OBJ_I_NO_DROP, "@@destruct_me");

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 1500);

    create_newbie_weapon();
}

void init()
{
    ::init();

    add_action("do_read","read");
}

int destruct_me()
{
    destroy_alarm = set_alarm(1.0, -1.0, "remove_obj");
    return 0;
}

void remove_obj()
{
    TO->remove_object();
}

int do_read(string str)
{
    if(!strlen(str))
        return 0;

    if(str == "label")
    {
        write(break_string("The label reads:\n\nSha'ang'sei equipment "+
            "services. Genuine hand-made "+short()+" of the finest quality "+
            "quality. Be warned that this equipment is worthless and has"+
            "been magically endowed to disintegrate when dropped.", 75));

        say(QCTNAME(TP)+" reads the label on "+POSSESSIVE(TP)+" "+
            short()+".\n");
        return 1;
    }
    return 0;
}
