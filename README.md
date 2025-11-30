

# 🍽️ Philosophers : Résolution du Problème des Dîners de Philosophes

## 🚀 Introduction

Le projet **Philosophers** est une implémentation en C du célèbre **Problème des Dîners de Philosophes**, un défi classique de la science informatique formulé par Edsger Dijkstra. Il modélise une situation où plusieurs processus (les philosophes) partagent des ressources limitées (les fourchettes) et doivent s'assurer d'éviter à la fois l'**interblocage (deadlock)** et la **famine (starvation)**.

Ce projet est conçu pour forger une compréhension solide de la **programmation concurrente** et de la **synchronisation de threads/processus**.

## 🎯 Objectifs et Enjeux Techniques

L'objectif principal est de simuler le comportement des philosophes (manger, dormir, penser) de manière parallèle, en garantissant qu'aucun philosophe ne meure de faim et que le système ne tombe jamais en *deadlock*.

### Concepts Clés Maîtrisés :

| Concept | Description et Application |
| :--- | :--- |
| **Multithreading** | Utilisation de la bibliothèque `pthread` pour représenter chaque philosophe comme un **thread** indépendant (Partie obligatoire). |
| **Processus** | Utilisation de `fork()` pour représenter chaque philosophe comme un **processus** distinct (Partie Bonus). |
| **Mutex / Sémaphores** | Implémentation de mécanismes de verrouillage (`mutex` dans la partie obligatoire, `sémaphores` dans le bonus) pour protéger les ressources critiques (les fourchettes) et prévenir les *race conditions*. |
| **Synchronisation** | Contrôle précis des actions des entités concurrentes, notamment pour : le partage des fourchettes, la gestion des logs, et la surveillance de l'état de chaque philosophe. |
| **Gestion du Temps** | Utilisation de fonctions précises pour suivre le temps écoulé (`gettimeofday` ou équivalent) et simuler la durée des actions (`usleep`). |
| **Prévention des Deadlocks** | Mise en œuvre d'une stratégie efficace (par exemple, un ordre strict d'acquisition des fourchettes ou une gestion asymétrique) pour garantir qu'aucun groupe de philosophes ne se bloque mutuellement. |

## 🍽️ Le Cycle de Vie du Philosophe

Chaque philosophe exécute un cycle de vie continu :

1.  **Penser** (Thinking)
2.  **Prendre les fourchettes** (Acquire Forks) : Le philosophe doit obtenir **les deux fourchettes adjacentes** pour manger.
3.  **Manger** (Eating) : Une fois les deux fourchettes acquises, le philosophe mange pendant un temps défini. Le temps depuis le dernier repas est réinitialisé.
4.  **Déposer les fourchettes** (Release Forks)
5.  **Dormir** (Sleeping)

## 🚨 Conditions d'Arrêt de la Simulation

La simulation se termine dans deux cas de figure :

1.  **Mort par Famine** : Si un philosophe ne mange pas avant que son `time_to_die` ne soit écoulé. Ce philosophe est déclaré mort et le programme s'arrête immédiatement.
2.  **Nombre de Repas Limité** : Si l'argument optionnel `number_of_times_each_philosopher_must_eat` est fourni et que tous les philosophes ont mangé ce nombre de fois.

## ⚙️ Installation et Utilisation

### Prérequis

  * `make`
  * `cc` (Compilateur C)
  * Librairie **`pthread`** (pour la partie obligatoire)
  * Librairie **`libft`** (si votre projet en dépend, voir note ci-dessous)

### Compilation et Exécution

**1. Compilation (Partie obligatoire - Threads)**

```bash
git clone https://github.com/myc42/philo
cd philo
make
```

**2. Utilisation**

Le programme est exécuté avec les arguments suivants, tous en millisecondes (ms) :

```bash
./philo <nombre_de_philosophes> <time_to_die> <time_to_eat> <time_to_sleep> [nb_max_repas]
```

| Argument | Description | Exemple |
| :--- | :--- | :--- |
| `nombre_de_philosophes` | Nombre de threads/processus à créer. | `5` |
| `time_to_die` | Temps maximal (en ms) avant qu'un philo ne meure s'il n'a pas mangé. | `800` |
| `time_to_eat` | Temps (en ms) que le philo met à manger. | `200` |
| `time_to_sleep` | Temps (en ms) que le philo met à dormir. | `200` |
| `nb_max_repas` (Optionnel) | Si présent, la simulation s'arrête quand tous ont mangé ce nombre de fois. | `7` |

**Exemple d'exécution :**

```bash
./philo 5 800 200 200 7
```

### ⚠️ Note Importante (Si dépendance à `libft`)

Si votre projet utilise des fonctions utilitaires de votre librairie personnelle (`libft`) et que la compilation échoue, assurez-vous de cloner et de placer `libft` dans le répertoire racine du projet :

> `git clone https://github.com/myc42/libft`
