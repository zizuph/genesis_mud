/*
* Primitive tool to create initial horse names data
* It contains horse's names and meanings.
 */

inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

/* Function Prototypes */
public int create_data();


void
create_object()
{
    ::create_object();
    setuid();
    seteuid(getuid());
    set_name(({"horse control", "control"}));
    set_pname("horse controls");
    set_adj("shiney");
    set_short("horse control");
    set_long("Type 'create' to overwrite /d/Shire/rivendell/steeds/horse_names'\n");
}


public int
create_data()
{
    mapping horse_data = ([ ]);
    horse_data["Telempe"] = ("Silver");
    horse_data["Ilsa"] = ("Silver");
    horse_data["Telpe"] = ("Silver");
    horse_data["Tinda"] = ("Silver");
    horse_data["Telpina"] = ("Silver");
    horse_data["Telpalak"] = ("Quicksilver");
    horse_data["Sisiila"] = ("Shine");
    horse_data["Laike"] = ("Acute");
    horse_data["Morwinyon"] = ("Glint in the Dark");
    horse_data["Melda"] = ("Beloved");
    horse_data["Faana"] = ("White Cloud");
    horse_data["Losselie"] = ("White");
    horse_data["Pilininge"] = ("Flight of Arrow");
    horse_data["Tasarin"] = ("Willow");
    save_map(horse_data, "/d/Shire/rivendell/steeds/horse_names");
    dump_mapping(horse_data, "\t");
    return 1;
}

init()
{
    ::init();
    add_action(create_data, "create");


}
