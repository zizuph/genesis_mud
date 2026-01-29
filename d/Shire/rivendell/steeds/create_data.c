/*
* Primitive tool to create initial horse data
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
    set_long("Type 'create' to overwrite /d/Shire/rivendell/steeds/horse_data'\n");
}


public int
create_data()
{
    mapping horse_data = ([ ]);
    horse_data["adj1"] = ({"confident", "high-spirited", "rogue", "muscular", "stately", "wild", "athletic", "painted", "regal", "shimmering","glimmering","majestic","proud","sleek","swift","spotted","speckled"});
    horse_data["adj2"] = ({"silvery","white","grey", "black and white"});
    horse_data["names"] = ({"Sulnim","Telempe","Ilsa","Telpe","Tinda","Telpina","Mirilli","Sisiila","Laike","Morwinyon","Pilininge","Melda","Losselie","Faana","Tasarin","Nolwe", "Orogas", "Athrithor", "Daraemaen", "Tundalian", "Elfos", "Nistion", "Daerion", "Emrel", "Pemor", "Manogil", "Elthron", "Minanoth", "Estochon", "Finrast", "Sereldel", "Rothrel", "Ivedir", "Armolleth", "Brethon", "Agluin", "Aralrin", "Aethor", "Araldath", "Bralil"});
    save_map(horse_data, "/d/Shire/rivendell/steeds/horse_data");
    dump_mapping(horse_data, "\t");
    return 1;
}

init()
{
    ::init();
    add_action(create_data, "create");


}
