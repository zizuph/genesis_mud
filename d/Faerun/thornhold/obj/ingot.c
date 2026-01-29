/* cold iron ingot by Twire, June 14, 2016
 * Item for the Thornhold merchants quest.
*/

inherit "/std/object";
public void
create_object()
{
    set_name("ingot");
    add_name("_thq_ingot");
    set_adj("cold iron");
    set_short("cold iron ingot");
    set_long("Cold iron is forged at a lower temperature than normal " +
             "iron or steel, in order to preserve its properties. It " + 
             "is mined deep underground, and is famed for its efficacy " +
             "against fey creatures.\n");
}
