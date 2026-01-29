/*
 * ebox.c
 *
 * This puts an enchantment on an object
 *
 * Ashlar, 6 Jul 97
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <filepath.h>
#include <macros.h>
#include <std.h>

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

#define CHECK_SO_WIZ 	if (WIZ_CHECK < WIZ_NORMAL) return 0; \
			if (this_interactive() != this_player()) return 0

string shadow_file = NOBJ + "enchantment";

int do_en(string what);
int do_unen(string what);
int do_eshadow(string what);

void
create_object()
{
    set_name("ebox");
    add_name("box");
    set_adj("enchantment");

    set_short("enchantment box");
    set_long("With this box you can test an enchantment " +
        "on an object in your inventory. Just type:\n" +
        "  en[chant] <object>\n  unen[chant] <object>\n" +
        "To select what shadow to use, type:\n" +
        "  eshadow <shadow>\n");
}

void
init()
{
    ::init();

    add_action(do_en, "en");
    add_action(do_en, "enchant");
    add_action(do_unen, "unen");
    add_action(do_unen, "unenchant");
    add_action(do_eshadow, "eshadow");
}

int
do_eshadow(string what)
{
    CHECK_SO_WIZ;

    NF("Syntax: eshadow <shadow file>\n");
    if (!what || (what == ""))
        return 0;

    shadow_file = FTPATH(this_interactive()->query_path(), what);
    write("Shadow file is now: " + shadow_file + "\n");
    return 1;
}
   
int
do_en(string what)
{
    object ob,en;
    string s;

    CHECK_SO_WIZ;

    NF("Enchant what?\n");
    if (!parse_command(what, this_player(), " %o ", ob))
        return 0;

    setuid();
    seteuid(getuid(this_object()));
    en = clone_object(shadow_file);
    if (!objectp(en))
    {
        write("Cannot clone the enchant shadow.\n");
        return 1;
    }

    if (s = en->enchant(ob,100))
    {
        
        en->remove_shadow();
        
        write("Cannot enchant the object: " + s + "\n");
        return 1;
    }

    write("You enchant the " + ob->short() + ".\n");
    return 1;
}

int
do_unen(string what)
{
    object ob;

    CHECK_SO_WIZ;

    NF("Unenchant what?\n");
    if (!parse_command(what, this_player(), " %o ", ob))
        return 0;

    if(ob->dispel_magic(100))
        write("You unenchant the " + ob->short() + ".\n");
    else
        write("Unenchant failed!\n");
    return 1;
}

