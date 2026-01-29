/*
 * Utility Functions for General Guild Support
 *
 * Created by Petros, March 2013
 */

#pragma strict_types

/* ====================================
 * FORMATTING UTILITY FUNCTIONS
 ======================================*/
/*
 * Function:    generate_scroll_text
 * Description: Wraps the input text with an ASCII scroll case.
 *              The text should not have length longer than 71 characters
 *              per line. The first line is the header. This will be
 *              automatically centered, and a header line placed beneath
 *              it. The rest of the text will automatically be wrapped.
 *              Note: The "property of.." text is hard-coded currently.
 */
public string 
generate_scroll_text(string content, string footer = "Property of This Guild")
{
    if (!strlen(content))
    {
        return "";
    }
    
    string output = "";
    string * lines = explode(content, "\n");
    int line_length = min(71, max(strlen(footer) + 10, applyv(max, map(lines, strlen)) + 1));
    
    // Create the scroll header
    output += sprintf("  %'_'" + sprintf("%d", line_length + 4) + "s\n", "");
    output += sprintf(" / \\%' '" + sprintf("%d", line_length + 2) + "s\\\n", "");
    output += sprintf("/___|%' '" + sprintf("%d", line_length + 2) + "s|\n", "");
    output += sprintf("|\\_/%'_'" + sprintf("%d", line_length + 2) + "s/\n", "");
    output += sprintf(" \\%' '" + sprintf("%d", line_length + 1) + "s\\\n", "");
    
    // Print the text header, centered
    output += sprintf("  \\ %|" + sprintf("%d", line_length) + "s\\\n", lines[0]);
    output += sprintf("   |%|" + sprintf("%d", line_length) + "s |\n", sprintf("%'='" + strlen(lines[0]) + "s", ""));
    // Now print the text itself
    foreach (string line : lines[1..])
    {
        output += sprintf("   | %-" + sprintf("%d", line_length) + "s|\n", line);
    }

    // Create the scroll footer
    output += sprintf("  /%' '" + sprintf("%d", line_length + 1) + "s/\n", "");
    output += sprintf(" /%'_'" + sprintf("%d", line_length) + "s /_\n", "");
    output += sprintf("|/\\%' '" + sprintf("%d", line_length + 2) + "s\\\n", "");
    output += sprintf("\\\\_|%|" + sprintf("%d", line_length + 2) + "s|\n", 
        "=== " + footer + " ===");
    output += sprintf(" \\/%'_'" + sprintf("%d", line_length + 2) + "s/\n", "");
    
    return output;
}
