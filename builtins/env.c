/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isouaidi <isouaidi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 07:59:10 by isouaidi          #+#    #+#             */
/*   Updated: 2024/04/26 19:42:47 by isouaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*convert_env(t_env *env, t_stru *stru, t_parser *list)
{
	int i;
	//int j;
	char **split;
	t_env *tes;

	i = 0;
	tes = env;
	if (env == NULL) {
		env = malloc(sizeof(t_env));
		tes = env;
		while (stru->env[i])
		{
			split = ft_split(stru->env[i], '=');
			env->name = ft_strdup(split[0]);
			if (split[1])
				env->value = ft_strdup(split[1]);
			else
				env->value = NULL;
			if (stru->env[i + 1] == NULL)
				env->next = NULL;
			else
				env->next = malloc(sizeof(t_env));
			free(split);
			env = env->next;
			i++;
		}
	}
	//export_env()
	doll1(list, tes);
	//tes = push_back_list(tes, "ilyes", "moi");
	//new_env(*(&tes), (*(&stru)));
	//chaine_env(tes);
	//built_env(tes);
	return (tes);
}

void	chaine_env(t_env *en)
{
	int i; 

	i = 0;
	while (en)
	{
		printf("name[%d] = %s\n",i, en->name);
		printf("value[%d] = %s\n\n",i, en->value);
		i++;
		en = en->next;
	} 	
}
char *check_dol(char *recup, t_env *env)
{	
	int i;
	int j;
	int d = 0;
	char quote = 0;
	char *str;
	char *apres;
	char *avant;
	char *va;

	j = 0;
	i = 0;
	while (recup[i])
	{	
		avant = malloc(sizeof(char) * (ft_strlen(recup + 1)));
		while (recup[i] && d != 1 )
		{
				quote = update_quote(quote, recup[i]);
				if (recup[i] == '$' && quote != '\'')
				{
					d = 1;
					break;
				}				
				avant[j++] = recup[i++];
		}
		avant[j] = '\0';
		if (recup[i] == '\0') 
		{
			va = ft_strdup("");
			d = 1;		
		}
		if (recup[i] != '\0')
			d = 0;
		j = 0;
		if ((recup[i] == '$' && recup[i + 1] == '\0') 
			|| ( recup[i + 1] == '"' && recup[i] == '$' && recup[i + 1] == '"' ))
				va = ft_strdup("$");	
		else if(recup[i] == '$' && d == 0 )
		{
			d = 0;
			va = malloc(sizeof(char) * (ft_strlen(recup + 1)));
			i++;
			while (recup[i] && recup[i] != '"' && recup[i] != '\'' && recup[i] != ' ' && recup[i] != '$')
				{
					quote = update_quote(quote, recup[i]);
					va[j++] = recup[i++];
				}
				va[j] = '\0';
					va = check_dollars(va, env);
		}
			d = 0;
			j = 0;
			apres = malloc(sizeof(char) * (ft_strlen(recup + 1)));
			while (recup[i])
			{
				quote = update_quote(quote, recup[i]);
				apres[j++] = recup[i++];
			}
			apres[j] = '\0';
			quote = update_quote(quote, recup[i]);
	}
	str = ft_mostrjoin(avant, va, apres);
	free(avant);
	free(apres);
	free(va);
	return(str);
}

void	doll1(t_parser *list, t_env *env)
{
	int j;
	char quote;
	
	j = 0;
	quote = 0;
	while (list)
	{
		j = 0;
		while (list->val[j])
		{
				quote = update_quote(quote, list->val[j]);
				if (list->val[j] == '$')
					list->val = check_dol(list->val, env);
				j++;
		}
		list = list->next;
	}
		
}

char	*check_dollars(char *str, t_env *env)
{
	char *va;
	int i;
	int j;

	i = 0;
	j = 0;
	va = ft_strdup("");
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
		{
			va = malloc(sizeof(char) * ft_strlen(env->value + 1));
			while (env->value[i])
				va[j++] = env->value[i++];
			va[j] = '\0';		
		}
		env = env->next;
	}
	return(va);
}

void built_env(t_env *env)
{
	while(env)
	{
		printf("%s", env->name);
		printf("=");
		if (env->value == NULL)
			printf("\n");
		else
			printf("%s\n", env->value);
		env = env->next;
	}
	printf("\n");
}
t_env *push_back_list(t_env *env, char *str, char *str2)
{
	t_env *element;
	t_env *check = env;
	t_env *temp;
	t_env *before;
	int f = 0;
	
	before = check;
	element = malloc(sizeof(t_env));
	element->name = strdup(str);
	element->value = strdup(str2);
	element->next = NULL;

	while (check)
	{
		if (ft_strcmp(check->name, element->name) == 0)
		{
			check->value = element->value;
			f = 1;
		}
		check = check->next;
	}
	temp = before;
	if (f == 0)
	{	
		
		while(temp->next != NULL)
			temp = temp->next;

		temp->next = element;
	}
	
	return (env);
}
