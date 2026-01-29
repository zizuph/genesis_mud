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
    set_adj("shiny");
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
    horse_data["Nolwe"] = ("Wild Wind");
    horse_data["Orogas"] = ("Spirited Warrior");
    horse_data["Athrithor"] = ("Noble Heart");
    horse_data["Daraemaen"] = ("Beloved One");
    horse_data["Tundalian"] = ("Noble One");
    horse_data["Elfos"] = ("Happiness");
    horse_data["Nistion"] = ("Bright Sky");
    horse_data["Daerion"] = ("Of Noble Birth");
    horse_data["Emrel"] = ("Precious Jewel");
    horse_data["Pemor"] = ("Joyful Heart");
    horse_data["Manogil"] = ("Beautiful Flower");
    horse_data["Elthron"] = ("Fiery Spirit");
    horse_data["Minanoth"] = ("Born of the Wind");
    horse_data["Estochon"] = ("Hero of Light");
    horse_data["Sereldel"] = ("One to be Honored");
    horse_data["Rothrel"] = ("Spirited Messenger");
    horse_data["Ivedir"] = ("Of the West");
    horse_data["Armolleth"] = ("Defender Against Darkness");
    horse_data["Brethon"] = ("Sacred Hunter");
    horse_data["Agluin"] = ("Bright One");
    horse_data["Aralrin"] = ("Silent Love");
    horse_data["Aethor"] = ("Victory Is at Hand");
    horse_data["Araldath"] = ("Silent River");
    horse_data["Bralil"] = ("Perfect Joy");

    save_map(horse_data, "/d/Shire/rivendell/steeds/horse_names");
    dump_mapping(horse_data, "\t");
    return 1;
}

init()
{
    ::init();
    add_action(create_data, "create");


}
