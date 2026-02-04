// Coffin objects for tomb02.c
// -- Lilith

inherit "/std/object";
#include <stdproperties.h>

string *adjs = (({ "simple","elaborate","carved","plain","ornate","painted"}));
string *type = (({ "wood", "granite", "marble"}));
string *cond = (({ "in good shape", "in bad shape", "falling apart"}));

void
create_object()
{
	string mytype = one_of_list(type);
	string myadj = one_of_list(adjs);
	string mycond = one_of_list(cond);
	
    set_name("coffin");
	add_name("_terel_tomb_coffin");
	set_adj(({ myadj, mytype }));
    set_short(myadj +" "+ mytype +" coffin");
    set_long("This "+ myadj +" coffin is made of "+ mytype +". It looks "+
        "like it is "+ mycond +".\n");
    add_cmd_item("coffin", "open", "The coffin is somehow locked, but you "+
        "can see no keyhole.\n");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);
}
     
