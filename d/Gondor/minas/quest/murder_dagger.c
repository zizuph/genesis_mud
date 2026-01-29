/*
 *  /d/Gondor/minas/quest/murder_dagger
 *
 *  The murder weapon in the whodunit quest
 *
 *  Olorin, 1-jun-1995
 */
inherit "/std/weapon";
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

int     bloody = 0;

void
set_bloody(int i)
{
    bloody = i;

    if (bloody)
    {
        add_adj("bloody");
        add_prop(OBJ_M_NO_SELL, "You will have to clean the dagger first!\n");
    }
    else
    {
        remove_adj("bloody");
        remove_prop(OBJ_M_NO_SELL);
    }
}

int     query_bloody() { return bloody; }

void
create_weapon()
{
    set_name("dagger");
    set_pname("daggers");
    set_short("ornate dagger");
    set_pshort("daggers");
    set_adj(({"sharp", "steel", "ornate", }));
    set_long("@@long_desc@@");

    // since it is found on the ground WC <= 10!
    set_default_weapon( 9, 10, W_KNIFE, W_SLASH|W_IMPALE, W_ANYH, 0);
    // give the weapon value, volume as for standard dagger:
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,16)+random(80)-20);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/4);

    add_item(({"blade", "letters"}), BSN(
        "Some letters are etched into the blade of the "+short()
      + ". They read: "
      + "Im Herumegil Hador Minas Tirith hain echant."));
    add_cmd_item(({"letters", }), "read", 
        "The letters etched into the blade of the "+short()+" read:\n"
      + "\tIm Herumegil Hador Minas Tirith hain echant.\n");
      
}

string
long_desc()
{
    string  desc =
        "This is an ornate steel dagger with a broad sharp blade and a "
      + "wooden hilt covered with leather.";

    if (bloody)
        desc += " Both blade and hilt are covered with blood.";

    desc += " There are some letters etched into the blade.";

    return BSN(desc);
}

void
init()
{
    ::init();

    add_action("do_clean", "clean");
}

int
do_clean(string str)
{
    string  vb = query_verb();

    if (!strlen(str) || !id(str))
    {
        NFN(CAP(vb)+" what?");
        return 0;
    }

    if (!bloody)
    {
        write("You try to "+vb+" the "+short()+", but as there is only "
          + "little dirt on it, your best efforts make little difference.\n");
        say(QCTNAME(TP)+" tries to clean "+LANG_ADDART(short())+", but has "
          + "little success in making a clean dagger even cleaner.\n");
        return 1;
    }

    write("You remove the blood from the hilt and the blade of the "
      + short() + ".\n");
    say(QCTNAME(TP)+" removes blood from the hilt and the blade of "
      + LANG_ADDART(short()) + ".\n");
    bloody = 0;
    remove_prop(OBJ_M_NO_SELL);
    return 1;
}

