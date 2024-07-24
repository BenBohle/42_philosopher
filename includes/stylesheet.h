/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stylesheet.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbohle <bbohle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:17:39 by bbohle            #+#    #+#             */
/*   Updated: 2024/07/24 15:46:35 by bbohle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define UNDERLINE "\033[4m"
#define BOLD "\033[1m"

void	start_screen(void);
void	wrong_input(void);
void	print_status(int id, const char *status, t_specs *specs);
void	print_status_dead(int id, const char *status, t_specs *specs);