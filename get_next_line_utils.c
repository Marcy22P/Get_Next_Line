/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpisani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:02:23 by mpisani           #+#    #+#             */
/*   Updated: 2025/01/24 15:35:14 by mpisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t gnl_strlen (const char *s)
{
    size_t len;

    size_t len = 0;
    if (!s)
        return(0);
    while(s[len])
        len++;
    return (len);
}

char gnl_strchr (const char *s, int c)
{
    if(!s)
        return(NULL);
    while (*s)
    {
        if(*s == (char)c)
            return ((char)*s);
        s++;
        
    }
    if (c == '\0')
        return ((char)*s);
    return (NULL);
}