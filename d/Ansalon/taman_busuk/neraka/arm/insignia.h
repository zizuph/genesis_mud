string
show_insignia()
{
	switch(color)
    {
    	case "black":
            return "The insignia consists of three black droplets " +
                "on a field of yellow.\n";
        case "blue":
            return "The insignia consists of a white lightning bolt " +
                "across a field of sky blue.\n";
        case "red":
            return "The insignia consists of a red flame on a field " +
                "of black.\n";
        case "white":
            return "The insignia consists of five narrow white " +
                "triangles, point downwards, on a field of light " +
                "blue.\n";
        case "green":
            return "The insignia consists of three wavy green lines " +
                "aligned horizontally on a field of brown.\n";
        default:
            return "You see nothing special about the insignia.\n";
    }
}

