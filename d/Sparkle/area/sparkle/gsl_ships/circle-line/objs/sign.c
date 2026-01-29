/*
 * Custom pier sign
 * for circle line
 */

#include "/d/Genesis/gsl_ships/ships.h";
#define COMPANY ("Genesis ShipLines")

#define PAD(width)             (sprintf("%' ' *s",width, " ") + "|   ||\n")
#define WRIT(width,text)       (sprintf("|%*|s|",width, text))
#define LINE(width, sym)       (sprintf("%'"+sym+"'-*s",width,sym))
#define MAX_SIGN_WIDTH 60
#define MIN_SIGN_WIDTH 32

inherit STDSIGN;

void
create_sign()
{
  ::create_sign();
}

varargs void
configure_sign (string port = "", int price = 0, string destination = "")
{
  int r, route_size;
  string *new_description;
  string *all_destinations;
  string prev_dest, next_dest;

  all_destinations = explode(destination, " - ");
  route_size = sizeof(all_destinations);
  for(r=0;r<route_size;r++) {
    if(all_destinations[r] == port) {
      prev_dest = r == 0 ?
        all_destinations[route_size-1] : all_destinations[r-1];
      next_dest = r == route_size-1 ?
        all_destinations[0] : all_destinations[r+1];
      break;
    }
  }
  new_description = ({});
  if(port != "")
    new_description += ({port + " office"});
  new_description += ({
    "Circle Line",
    "",
    "Arrival from: " + prev_dest,
    "Departure to: " + next_dest,
    "The ride is free"
  });

  if(!sizeof(new_description))
    new_description = ({"This pier is currently unused"});
  //set_long(get_label(new_description));
  Sign_Desc = get_label(new_description);  
}

public string
get_label (string *lines)
{
  int max_width, pad_width, text_width;
  string label;

  max_width = applyv(max, map(lines, strlen)) + 10;
  if(max_width > MAX_SIGN_WIDTH)
		max_width = MAX_SIGN_WIDTH;
  if(max_width < MIN_SIGN_WIDTH)
    max_width = MIN_SIGN_WIDTH;
  text_width = max_width + 2;
  pad_width = 60 - max_width;
  label =
    "                      ______________________________________________.^.\n"+
    "                   .'.--------. .---------------------.___________  ==-`.\n"+
    "              ___.-_________.-'___                            | (0)|   ||\n"+
    "            . .--\\_---------\\_--. .                            `.__|   ||\n";
  label +=
    "   .--------||-------------------||" + LINE(max_width-29,"-") +
    "." + PAD(pad_width);
  label +=
    " ." + LINE(text_width, "-") + ".'|"+
    PAD(pad_width);
  label +=
    " " + WRIT(text_width, COMPANY) + " |" + PAD(pad_width);
  label +=
    " " + WRIT(text_width, " ")     + " |" + PAD(pad_width);
  foreach(string line: lines) {
		label +=
      " " + WRIT(text_width, line) + " |" + PAD(pad_width);
  }
  label+=
    " |"+ LINE(text_width, "_") +
    "|.'"+
    PAD(pad_width);

  return label;
}
    
