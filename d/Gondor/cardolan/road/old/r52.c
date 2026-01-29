inherit "/d/Gondor/gus/lib/road";

create_room() 
{
 street = "The Greenway";
 where = "north";
 county = "Cardolan";
 land = "lost realm of Arnor";
 mountain = "South Downs";
 vegetation = "fragrent herbs and thorn bushes";
 extraline = "You are on a treelined road which is overgrown with tall grass."
           + " Looking around you see the " +vegetation
           + " covering the land of " +county+ ". The road looks better"
           + " travelled to the north beyond a forbidding looking hedge"
           + " through which the road passes. You see steep hills to both sides.";

 add_item((({"hill","hills","downs"})),"To the east, steep hills end in stony escarpments.\n"+"They look unscalable for now. \n\n");
 add_exit("/d/Gondor/zephram/cardolan/road/r53", "north", 0);
 add_exit("/d/Gondor/zephram/cardolan/road/r51", "south", 0);

 make_the_room();
}

reset_room();

query_road()
{
 return 1;
}

