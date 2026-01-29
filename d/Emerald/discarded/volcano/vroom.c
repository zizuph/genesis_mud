inherit "/std/room";

void create_volcano();
string vol_desc();

void
create_room()
{
    set_long(vol_desc());
	add_item(({"rocks", "pebbles", "gravel", "stones"}), "Various sizes of "+
	"rocks and stones cover the ground.\n");
    add_item(({"lava"}), "Cooled lava lines the ground in patches, " +
        "the only remnants of past eruptions.\n");
    add_item(({"seagulls", "seagull", "bird", "birds"}), "Seagulls " +
        "squawk nosily overhead, searching the nearby waters for " +                  
        "food.\n");
    add_item(({"plant", "plants", "brush"}), "Hearty, mid-sized plants " +
	"grow up between the gravel and rocks.\n");
    
    create_volcano();
}

string
vol_desc()
{ 
    switch(random(6))
    {
      case 0:
      return "   You stand on the steep slope of the side of the" +
        " volcano. You wonder how many people have " +
        "made it this far. You survey how far you have come and " +
	"feel a sense of pride, but you realize its a long climb " +
	"to the top, but if you push on, you can make it.\n\n";
      break;
      
      case 1:
      return"   You stop a moment to catch your breath after" +
        " the steep climb. " +
        "You stand on the side of the volcano to take a quick rest from " +
        "the tiring climb that is part of your journey.  Seagulls fly" + 
        " overhead and the path you stand on is covered with rocks and" +  
        " pebbles.\n\n";
      break;

      case 2:
      return "   You stand upon a path littered with rubble, rocks, and " +
	"cooled lava, which remains from the last eruption of this large " +
	"volcano. Looking around, you can see some plants starting to grow " +
	"on the ground in the gravel, and by their size, you assume " +
	"it has been a while since the last eruption.\n\n";
      break;

      case 3:	
      return "   The ground beneath your feet crunches as you walk " +
	"Beneath your feet is ground covered with small rocks and gravel " +
	"Hear and there some plants manage to sprout up between the patches " +
	"of dried lava. You would gather there hasn't been an eruption " +
	"in some time.\n\n";
      break;

      case 4:
      return "   You carefully climb up the steep slope of the side of " +
	"the volcano. Despite it being tiring, the climb isn't as hard as " + 
	"you had imagined. Rocks and stones litter the path on which you " + 
	"walk. Here and there are dried remenants of lava, the only " + 
	"indicator this volcano might still be active. However, since " +
	"plants manage to grow between the rocks, you imagine it has been " +
	"a long time since the last eruption.\n\n";
     break;

     case 5:
	return "   As you survey the land around you, you notice smoke " +
	"puffing out of the mouth of the volcano. Looking at the ground " +
	"you, you notice the path is covered with small rocks and " +
	"pebbles, but here and there plants mange to grow between the " +
	"rocks, an indicator that the volcano has not erupted for a long " +
	"time.\n\n";
	break;
	     
     default:
     return "   You grow weary as you continue your effort to reach " +
        "the peak. You glance around at the scenery as you gather the " + 
	"energy to go on. Rocks and pebbles adorn your path. Looking down " +
        "you can see the water lapping on the shore.  Looking up, you can" +
        " see the smoke billowing from the top of the volcano.\n\n";
      break;
    }
}

void
create_volcano()
{
}

