/* spice tin by Twire, June 14, 2016
 * Item for the Thornhold merchants quest.
*/

inherit "/std/object";
public void
create_object()
{
    set_name("tin");
    add_name("_thq_spice_tin");

    set_adj("brass");
    set_adj("silver");
    set_adj("small");
    set_short("small silver spice tin");
    set_long("A silver spice tin for storing rare spice blends.\n");
}
