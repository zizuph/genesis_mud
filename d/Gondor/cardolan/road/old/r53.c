inherit "/d/Gondor/gus/lib/road";

create_room() 
{
 street = "The Greenway";
 where = "north";
 county = "Cardolan";
 land = "lost realm of Arnor";
 mountain = "Barrow Downs";
 vegetation = "fragrent herbs and thorn bushes";
 extraline = "You are on a treelined road which is overgrown with tall grass."
           + " Looking around you see the " +vegetation
           + " covering the land of " +county+ ". The road looks better"
           + " travelled to the north beyond a forbidding looking hedge"
           + " through which the road passes. You see steep hills to both sides.";

 add_item((({"hedge","thorn","bushes"})),"Just north of you is a high hedge of thorn bushes on a strange\n"+"looking long mound. Perhaps it is the remains of an ancient wall which\n"+"has long since fallen into disrepair. \n\n");
 add_item((({"hill","hills","downs"})),"The "+mountain" to the west look like diseased green gums. \n" + "To the east, the South downs look less forbidding but no less \n" + "unclimbable, at least for now. \n\n");
 add_exit("/d/Gondor/zephram/cardolan/road/r52", "south", 0);

 make_the_room();
}

reset_room();

query_road()
{
 return 1;
}

