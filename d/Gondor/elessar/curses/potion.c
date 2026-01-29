/*
 * /doc/examples/poison/potion.c
 * Written by Quis, 920605
 */

inherit "/std/drink.c";

/*
 * We just make a generic drink, with no healing powers.
 */

create_drink()
{
    set_soft_amount(0); 
    set_alco_amount(0); 
    set_name("potion"); 
    set_short("potion"); 
    set_long("This potion bubbles and fumes.\n"); 
}

/*
 * We need to intercept the activating command for the drink.
 * so, we redefine drink_one_thing() from /std/drink.c
 */

int
drink_one_thing(object ob)
{
    int check;
    object poison;

/*
 * First, we call the original function.  Only if non-zero is returned do
 * we start the poison.  We will eventually return the original
 * drink_one_thing value.
 */
    check = ::drink_one_thing(ob);
    if(check) {
/*
 * Now we create the poison.  We will just use the defaults, so no set_*
 * functions are required.  After we clone it, we move it to the
 * consuming living, then call the activating function, start_poison()
 */
        poison = clone_object("/std/poison_effect");
        if(poison) {
          poison->move(this_player());
          poison->start_poison();
        }
        else 
          write("Failed to load poison for some reason.\n"); 
    }

    return check;
}
