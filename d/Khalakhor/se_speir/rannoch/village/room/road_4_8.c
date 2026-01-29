/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_4_8.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-09  
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : The marketplace
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"

#include "room.h"

inherit VILLAGE_BASEFILE;

int approach_vegetable_merchant();
int approach_fruit_merchant();
int approach_berry_merchant();
int approach_mushroom_merchant();
int approach_fish_merchant();
int approach_egg_merchant();
int approach_milk_merchant();
int approach_bread_merchant();
int approach_poultry_merchant();

int
approach_vegetable_merchant()
{
    write("You approach the vegetable merchant, a middle-aged "
        + "man standing in front of three carts. He smiles at "
        + "you and says: - Vegetables! Today I have potatoes, "
        + "carrots, really nice turnips, cabbage, and some "
        + "fresh radishes when the wife returns. Whatever you "
        + "need, it's ten silver coins a bag.\n");
    say(QCTNAME(this_player())+ " approaches the vegetable "
                              + "merchant.\n");
    return 1;
}
int
approach_fruit_merchant()
{
    write("You approach the fruit merchant, a skinny young "
        + "man sitting on a stool behind a makeshift table. "
        + "He looks up at you and says: - You need fruit? "
        + "Well, nothing exotic today, just the usual apples, "
        + "pears, and prunes from the garden. But they come "
        + "cheap! Fifteen silver for one bag of one fruit of "
        + "your choice. So, you'll take ten bags?\n"
        + "The fruit merchant smiles hopefully.\n");
    say(QCTNAME(this_player())+ " approaches the fruit "
                              + "merchant.\n");
    return 1;
}
int
approach_berry_merchant()
{
    write("You approach the merchant selling nuts and berries, "
        + "a poor middle-aged woman surrounded by five baskets. "
        + "She sighs and says: - You've come to the right place, "
        + "I have a fresh load of cloudberries, cranberries, "
        + "and juniper berries. Then there's always the ususal "
        + "bunch of mixed nuts there, and if Ciara returns "
        + "soon we'll have some wild strawberries for sale. I "
        + "don't have any baskets or bags, you'll have to carry them "
        + "in your hand, I'm afraid. But it's only two silver per "
        + "handful.\n");
    say(QCTNAME(this_player())+ " approaches the berry merchant.\n");
    return 1;
}
int
approach_mushroom_merchant()
{
    write("You approach the man who looks like he tries to sell "
        + "mushrooms, an old dirty man wearing brown rags. He is "
        + "clearly insane, but has managed to fill ten old hats "
        + "with mushrooms. As you approach him he squirms a while, "
        + "then says: - Mushrooms! Mushrooms! I be the mushroom "
        + "monger, and you am lucky! Hoho, lots of them little "
        + "fellows, picked them myself I did. Look, here you have "
        + "chanterelles, ceps, puffballs, and these little funny "
        + "white ones. Just one silver a piece!\n");
    say(QCTNAME(this_player())+ " approaches the mushroom merchant.\n");
    return 1;
}
int
approach_fish_merchant()
{
    write("You approach a big red-bearded man wearing warm clothing, "
        + "standing among a few barrels and small carts. You feel "
        + "an overwhelming stench of fish when he says: - Looking for "
        + "some fish, eh? Well I always keep a fresh stock. The catch "
        + "of the day includes bass, pike, ruff, and trout. But come "
        + "back any day and hopefully there'll be more. But let's get "
        + "down to business. Only five silver each, one for the ruffs. "
        + "What do you say?\n"
        + "The fishmonger holds up a large bass and smiles proudly.\n");
    say(QCTNAME(this_player())+ " approaches the fish merchant.\n");
    return 1;
}
int
approach_egg_merchant()
{
    write("You approach a small woman accompanied by three children. "
        + "She glares at you for a moment then picks up a basket "
        + "full off eggs. She smiles and says: - These eggs "
        + "comes from the finest hens in the village. Perfect for "
        + "bread or pancakes, or just fry them up. But I only sell "
        + "by the score you know, that's ten silver for twenty eggs. "
        + "All right kids, we have a customer here!\n");
    say(QCTNAME(this_player())+ " approaches the egg merchant.\n");
    return 1;
}
int
approach_milk_merchant()
{
    write("You approach a fat woman currently involved in devouring "
        + "a big slice of cheese. While still chewing she says: - "
        + "What do you need then? I have milk and lots of it, from "
        + "the best cows for miles around. But I also sell butter "
        + "and cheese. That'll cost you five silver for a bottle "
        + "of milk, ten silver for a lump of butter, and thirty "
        + "silver for a small cheese. Big ones cost tenfold.\n"
        + "The woman looks expectantly at you.\n");
    say(QCTNAME(this_player())+ " approaches the milk merchant.\n");
    return 1;
}
int
approach_bread_merchant()
{
    write("You approach a thin man wearing a white apron standing in "
        + "a large booth, and after finishing another deal he turns "
        + "to you and says: - Hello hello, you look like you need some "
        + "newly baked bread. Then I'm just the man you need. Oh yes, I "
        + "just got these loaves out of the oven, and there's quite a "
        + "few scones left for you. That'll be five silver for a loaf, "
        + "and two silver for a scone.\n"
        + "The bakerman starts preparing a bag for you.\n");
    say(QCTNAME(this_player())+ " approaches the bread merchant.\n");
    return 1;
}
int
approach_poultry_merchant()
{
    write("You approach a large man clad in furs, standing in front "
        + "a rickety stand, with many kinds of birds hanging from "
        + "it. He notices you and says in a booming voice: - Come "
        + "here and have a look will you? I have some chickens, of "
        + "course, only six silver each, and just for you my friend "
        + "I have these pheasants for a meager twenty silver each. "
        + "Do we have a deal?\n");
    say(QCTNAME(this_player())+ " approaches the poultry merchant.\n");
    return 1;
}
public void
create_road()
{
    add_item(({"merchant","merchants","hawker","hawkers"}),
               "Scattered across the marketplace, the merchants "
             + "display their goods using what they have available, "
             + "be it booths, carts, piles of boxes, or just a "
             + "piece of cloth on the ground. Some wares for sale "
             + "at the moment are vegetables, fruit, berries, "
             + "mushrooms, fish, poultry, eggs, milk and bread. Just "
             + "approach a merchant selling what you are looking "
             + "for to get more information.\n");
    add_item(({"vegetable merchant"}),
               "He is a balding middle-aged man, with big dirty hands "
             + "and his clothes is covered with stains and dirt. He "
             + "is standing in front of three large carts, and they "
             + "contain a mixed assortment of vegetables. They don't "
             + "look as they have been cleaned at all.\n");
    add_item(({"fruit merchant"}),
               "He is a skinny young man clad in clean clothes, a rare "
             + "sight in these parts, and he is sitting behind a rickety "
             + "table made out of a couple of boards and an empty box. "
             + "In front of the table are more boxes, some without any "
             + "bottom. They all smell horribly of rotten fruit, but "
             + "at least the displayed fruit seems fresh enough.\n");
    add_item(({"berry merchant"}),
               "She is a poor middle-aged woman dressed only in a simple "
             + "dress and a bonnet. On the ground around her you see a "
             + "number of baskets, all containing varied amounts of "
             + "berries and nuts. They look to be of high quality, "
             + "someone went through a lot of trouble to gather all this.\n");
    add_item(({"mushroom merchant"}),
               "He is a filthy old man, wearing disgusting rags and a "
             + "tattered cap. He is talking to himself quietly, now "
             + "and then grinning or muttering. By his shoeless feet "
             + "he has put a number of old hats, all filled with "
             + "different kinds of mushrooms. No doubt he has found "
             + "some spots in the woods where they grow abundant, "
             + "but he seems to lack customers for some reason.\n");
    add_item(({"fish merchant"}),
               "He is a large, red-bearded man wearing warm clothes and "
             + "holding a large fish in each hand. The unmistakable "
             + "smell of fish spreads from both him and the barrels "
             + "and carts around him. A really fat grey cat lies at his "
             + "feet, sleeping soundly.\n");
    add_item(({"egg merchant"}),
               "She is a small, busy human with a gentle smile and "
             + "a squeaky voice. On the ground beside her are four "
             + "baskets, full off eggs. Standing very close to the "
             + "woman are three children, all desperate for their "
             + "mother's attention.\n");
    add_item(({"milk merchant"}),
               "She is a really large woman, dressed in otherwise "
             + "clean clothes save the crumbs and food stains. She "
             + "seems to eat more than she sells, and doesn't look "
             + "like she enjoys being here. Behind on her on a cart "
             + "you notice piles of cheese, some small boxes, and "
             + "large cans of what must be milk.\n");
    add_item(({"fat cat","grey cat","fat grey cat","cat"}),
               "Sleeping comfortably by the fish merchant's feet you "
             + "see what must be the most well-fed cat for miles around. "
             + "His shiny, thick fur and the size of him also marks "
             + "as the probably most hated creature by all the other "
             + "cats in the village.\n");
    add_item(({"old woman","ugly old woman","onion lady","gossip monger",
               "ugly woman"}),
               "Of all the things you have seen in Khalakhor, this "
             + "is the most repulsive living being you have ever laid "
             + "your eyes upon. However, there is an air of authority "
             + "around her, and people treat her with respect. She "
             + "sits on a simple chair next to a warehouse, and very "
             + "little escapes her gaze. She has a basket of yellow "
             + "onions in her lap.\n");

    add_cmd_item("vegetable merchant","approach",approach_vegetable_merchant);
    add_cmd_item("fruit merchant","approach",approach_fruit_merchant);
    add_cmd_item("berry merchant","approach",approach_berry_merchant);
    add_cmd_item("mushroom merchant","approach",approach_mushroom_merchant);
    add_cmd_item("fish merchant","approach",approach_fish_merchant);
    add_cmd_item("egg merchant","approach",approach_egg_merchant);
    add_cmd_item("milk merchant","approach",approach_milk_merchant);
    add_cmd_item("bread merchant","approach",approach_bread_merchant);
    add_cmd_item("poultry merchant","approach",approach_poultry_merchant);

    add_exit(ROOM + "road_3_8.c","west",0,1,0);
    add_exit(ROOM + "road_3_7.c","northwest",0,1,0);
    add_exit(ROOM + "road_4_7.c","north",0,1,0);
    add_exit(ROOM + "road_5_7.c","northeast",0,1,0);
    add_exit(ROOM + "road_5_8.c","east",0,1,0);
    add_exit(ROOM + "road_5_9.c","southeast",0,1,0);
    add_exit(ROOM + "road_4_9.c","south",0,1,0);
    add_exit(ROOM + "road_3_9.c","southwest",0,1,0);

    set_short("marketplace");
    set_long("Approach merchants.\n");
}
