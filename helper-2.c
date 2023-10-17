#include "shell.h"

ssize_t get_new_len(char *line);
void handle_line(char **line, ssize_t read);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Line from stdio.
 * @line: A pointer.
 * @read: The length.
 * 
 */
void handle_line(char **line, ssize_t read)
{
        char *old_line, *new_line;
        char previous, current, next;
        size_t in, je;
        ssize_t new_len;

        new_len = get_new_len(*line);
        if (new_len == read - 1)
                return;
        new_line = malloc(new_len + 1);
        if (!new_line)
                return;
        je = 0;
        old_line = *line;
        for (in = 0; old_line[in]; in++)
        {
                current = old_line[in];
                next = old_line[in + 1];
                if (in != 0)
                {
                        previous = old_line[in - 1];
                        if (current == ';')
                        {
                                if (next == ';' && previous != ' ' && previous != ';')
                                {
                                        new_line[je++] = ' ';
                                        new_line[je++] = ';';
                                        continue;
                                }
                                else if (previous == ';' && next != ' ')
                                {
                                        new_line[je++] = ';';
                                        new_line[je++] = ' ';
                                        continue;
                                }
                                if (previous != ' ')
                                        new_line[je++] = ' ';
                                new_line[je++] = ';';
                                if (next != ' ')
                                        new_line[je++] = ' ';
                                continue;
                        }
                        else if (current == '&')
                        {
                                if (next == '&' && previous != ' ')
                                        new_line[je++] = ' ';
                                else if (previous == '&' && next != ' ')
                                {
                                        new_line[je++] = '&';
                                        new_line[je++] = ' ';
                                        continue;
                                }
                        }
                        else if (current == '|')
                        {
                                if (next == '|' && previous != ' ')
                                        new_line[je++]  = ' ';
                                else if (previous == '|' && next != ' ')
                                {
                                        new_line[je++] = '|';
                                        new_line[je++] = ' ';
                                        continue;
                                }
                        }
                }
                else if (current == ';')
                {
                        if (in != 0 && old_line[in - 1] != ' ')
                                new_line[je++] = ' ';
                        new_line[je++] = ';';
                        if (next != ' ' && next != ';')
                                new_line[je++] = ' ';
                        continue;
                }
                new_line[je++] = old_line[in];
        }
        new_line[je] = '\0';

        free(*line);
        *line = new_line;
}

/**
 * get_new_len - Gets ";", "||", "&&&", or "#".
 * @line: Line check.
 * Return: New length.
 */

ssize_t get_new_len(char *line)
{
        size_t i;
        ssize_t new_leng = 0;
        char curr, nxt;

        for (i = 0; line[i]; i++)
        {
                curr = line[i];
                nxt = line[i + 1];
                if (curr == '#')
                {
                        if (i == 0 || line[i - 1] == ' ')
                        {
                                line[i] = '\0';
                                break;
                        }
                }
                else if (i != 0)
                {
                        if (curr == ';')
                        {
                                if (nxt == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
                                {
                                        new_leng += 2;
                                        continue;
                                }
                                else if (line[i - 1] == ';' && nxt != ' ')
                                {
                                        new_leng += 2;
                                        continue;
                                }
                                if (line[i - 1] != ' ')
                                        new_leng++;
                                if (nxt != ' ')
                                        new_leng++;
                        }
                        else
                                logical_ops(&line[i], &new_leng);
                }
                else if (curr == ';')
                {
                        if (i != 0 && line[i - 1] != ' ')
                                new_leng++;
                        if (nxt != ' ' && nxt != ';')
                                new_leng++;
                }
                new_leng++;
        }
        return (new_leng);
}
/**
 * logical_ops - Check "||" or "&&".
 * @line: Character to check.
 * @new_len: Pointer.
 */

void logical_ops(char *line, ssize_t *new_len)

{
        char prev, curr, nxt;

        prev = *(line - 1);
        curr = *line;
        nxt = *(line + 1);

        if (curr == '&')
        {
                if (nxt == '&' && prev != ' ')
                        (*new_len)++;
                else if (prev == '&' && nxt != ' ')
                        (*new_len)++;
        }
        else if (curr == '|')
        {
                if (nxt == '|' && prev != ' ')
                        (*new_len)++;
                else if (prev == '|' && nxt != ' ')
                        (*new_len)++;
        }
}

