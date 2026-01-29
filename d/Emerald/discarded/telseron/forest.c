/*
 * The forest clearing before Telseron
 * Coded by Finwe
 * February 1997
 * add_items are borrowed from ~emerald/forest/
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
// inherit "/d/Gondor/open/HERBS/herbsearch";
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("A large clearing");
    set_long("   You stand in a large clearing in the forest. The " +
        "trees are large and green. A few have fallen and lay on " +
        "the ground as moss covered logs. Under the trees you see " +
        "fallen branches and leaves. A wide track runs northeast " +
        "and southeast. Northeast the clearing continues. Southeast, " +
        "you see the glorious city of Telseron shining brightly in " +
        "the sunlight.\n\n");
 
    add_item(({"forest", "trees"}), "The forest consists of a blend of"+
        " deciduous trees, but most prominent is perhaps the"+
        " majestic poplars which tower high above you. The ground"+
        " is blanketed in a carpet of thick grass, growing in the"+
        " dim light that filters down through the foliage.\n");
    add_item(("life"), "The forest is burstling with life, birds singing"+
        " in the trees, insects buzzing among the flowers."+
        " Sometimes youeven catch a glimpse of a deer grazing.\n");
    add_item(("grass"), "The grass seem to thrive, and covers the ground"+
        " like a soft green carpet. You notice some withered leaves"+
        " and dry twigs are nestled in the thick grass, as well as"+
        " a few flowers shooting up here and there, spreading a"+
        " sweet scent in the air.\n");
    add_item(("birds"), "You actually don't see much of the birds, apart"+
        " from when they swoop down to snatch a few flies, but the"+
        " air is filled with their delightful twittering.\n");
    add_item(("insects"), "You see all kinds of insects; butterflies"+
        " fluttering around, small flies swirling in the air and"+
        " bumblebees flying from flower to flower.\n");
    add_item(("butterflies"), "The butterflies are brightly coloured,"+
        " with vivid patterns on their wings.\n");
    add_item(("bumblebees"), "The bumble bees make a low humming sound,"+
        " as they fly from flower to flower.\n");
    add_item(("ground"), "Thick grass covers the ground like a carpet, a"+
        " few flowers shoot up in the grass, spreading a sweet"+
        " scent in the air.\n");
    add_item(("leaves"), "The leaves are grey-green with a fine silvery"+
        " down coating their surface. The down seems to make the"+
        " leaves glow like burnished bronze in the sun.\n");
    add_item(("bark"), "The bark is dark grey with a smooth almost shiny"+
        " lustre. The bark glows with a warm bronze-like gleam when"+
        " the sun hits it, creating unique patterns on the trunks"+
        " in bronze and silver grey.\n");
    add_item(("trunks"), "The massive trunks resemble pillars, their"+
        " smooth grey bark resembles polished stone streaked"+
        " with bronze, as the sun shines down on them.\n");
    add_item(("sun"), "Now and then you can catch short glimpse of the"+
        " sun glittering through the foliage.\n");
    add_item(("poplars"), "The poplars are truely majestic. Their trunks"+
        " rise like massive pillars, then split up into several"+
        " heavy branches that stretch across the sky, to finally"+
        " end up in a thick crown of leaves.\n");
    add_item(({"foliage", "roof"}), "The foliage sways sthe"+
        " wind above you. Its mass of leaves shading you, like a"+
        " dark against the sky.\n");
    add_item(("flowers"), "All kinds of flowers in vibrant colours from"+
        " crimson to azure grow in small clusters in the grass. The"+
        " flowers emit a sweet scent of nectar to the air. You can"+
        " hear a soft buzzling sound from bumble-bees as they buzz"+
        " from flower to flower in their hunt for nectar.\n");
    add_item(("twigs"), "A few dry twigs lay strewn around in the grass."+
        " They probably remain there since the last year's autumn" +
        "storms.\n");
    add_item(("withered leaves"), "Some leaves have fallen down from the"+
        " trees, and are now laying crumpled in the grass.\n");
    add_item(( {"log", "log"}),
        "The logs are half rotted and moss covered. Small animals " +
        "seem to use some of them as havens from the forest. Some " +
        "of the logs look like they have been clawed by larger " +
        "animals searching for food. Growing out from under them " +
        "you see young plants.\n");
    add_item("young plants", 
        "Many young plants grow here in the clearing. Some grow " +
        "out from under the logs. They are green and healthy " +
        "looking.\n");
    add_item( ({"glorious city of Telseron", "telseron", "Telseron",
            "glorious city of telseron", "city"}),
        "The beautiful elven city shines brightly in the " +
        "sunlight. It appear to be quite prosperous.\n");
 
    set_alarm(1.0,0.0,"reset_room");
/*
   set_up_herbs(({OBJ_DIR + "blackberry", OBJ_DIR + "carmoth"}),
      ({"grass", "ground"}), 4);
suranie, fungiarbo
*/
 
    add_exit(KROAD_DIR + "road22", "northeast", 0, 4);
    add_exit(TOWNSHIP_DIR + "rd01", "southeast"); 
}
 
int
no_way()
{
    write("The royal family of Telseron have closed the city. " +
        "The branches close about you, preventing travel further " +
        "south from here.\n");
    return 1;
}
 
 
void
reset_room()
{
}
