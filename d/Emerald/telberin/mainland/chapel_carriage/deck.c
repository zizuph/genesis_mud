inherit "/d/Emerald/telberin/mainland/chapel_carriage/basedeck";

public void
create_deck()
{
     set_short("Inside the Emerald Carriage");
     set_long("   You are sitting inside the emerald carriage. The seats "+
	      "are thick, brown leather, the doors, walls and handles are all "+
	      "wood which has been stained or painted in an emerald "+
	      "green and trimmed with gold. Even the windows are made "+
	      "of a glass which carries a slightly green tint.\n\n");

     add_item(({"seats", "leather"}),
	      "The seats are made of a fine, brown leather.\n");
     add_item(({"doors", "walls", "handles"}),
	      "The doors, walls and handles are all made of a wood which "+
	      "has been painted green and trimmed with gold-painted "+
	      "metal.\n");

     set_deck_sound("The carriage rumbles along.\n");

     add_item("carriage","You are sitting inside it.\n"); 
     add_item("window","It is a nice-looking window.\n");
}

public int
special_disembark()
{
    return 0;
}
