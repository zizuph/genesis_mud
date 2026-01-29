
#pragma strict_types

inherit "/std/drink";


public void 
create_drink()
{
    set_soft_amount(0); 
    set_alco_amount(0); 
    set_name("potion"); 
    set_adj("scarlet-red");
    set_short("scarlet-red potion"); 
    set_long("This scarled-red potion bubbles and smells like " +
		"Death himself.\n"); 
}

public mixed
command_drink()
{
    int check;
    object *inv;
    int i;
    int strength;
    string *types;

    strength = 1000;
    types = ({"red death"});

    check = ::command_drink();
    if(check) {
        inv = all_inventory(this_player());
        for (i = 0; i < sizeof(all_inventory(this_player())); i++ ) {
            if(function_exists("cure_poison",inv[i])) 
                inv[i]->cure_poison(types, strength);
        }
    }

    return check;
}
