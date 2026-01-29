/* A simple key to the door examples by Nick */
/* Modified by Marisol (02/22/99) to be used in the castle 
 * at Ovejuno in Emerald. */


inherit "/std/key";

create_key()
{
    set_adj("intrincate");
    add_adj("silver");
    set_long("This is the master key of the castle. It is a "+
        "intrincate, silver key that will open all known rooms "+
        "in the castle.\n");
    set_key("ovejuno castle master key");
}
