inherit "/d/Gondor/elessar/lib/field";

create_room()
{
    areatype = 8;
    areadesc = "stone bridge";
    area = "bordering";
    areaname = "Anorien and Rohan";
    land = "Gondor";
    extraline = "The stone bridge is quite solid, and is one of the crossings of "+
    "the Mering Stream, the little river that forms the border between Gondor "+
    "and Rohan. To the southeast you see Anorien, with its green fields, and "+
    "to the northwest are the plains of Rohan. The Mering Stream continues "+
    "towards the northeast, where it merges with the Entwash.";
    add_item("bridge","The bridge is quite old, and it is one of two crossings\n"+
      "of the Mering Stream. It is built up of white stones from the quarries\n"+
      "in the White Mountains.\n");
    add_item(({"mering stream","stream","mering"}),
      "This is the small stream forming the border between Rohan and Gondor.\n"+
      "Its sources are high up in the White Mountains, and it flows through the\n"+
      "Firienwood and the green fields of the East Emnet before it joins the\n"+
      "River Entwash somewhere in the soggy marshes of the Vale of Entwash.\n");
    add_exit("/d/Gondor/rohan/plains/b11","north",0,2);
    add_exit("/d/Gondor/anorien/plains/w1","south",0,2);
    make_the_room();
}

