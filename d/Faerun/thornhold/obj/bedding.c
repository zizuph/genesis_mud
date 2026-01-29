/* Bedding for the bunkhouse loupe by Twire, June 14, 2016
 * Item for the Thornhold merchants quest.
*/

inherit "/std/object";
public void
create_object()
{
    set_name("bedding");
    add_name("bunkhouse_inn_key");
    set_adj("bunkhouse");
    set_short("bedding for the bunkhouse");
    set_long("This is simple bedding but looks comfortable enough to sleep in for " +
             "a night.\n");
}
