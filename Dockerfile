FROM amd64/debian:stable

# Mettre à jour le système et installer les outils de base ainsi que les dépendances nécessaires
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y sudo git build-essential net-tools vim libc6-dev linux-libc-dev iputils-ping tcpdump valgrind

# Copier les fichiers du projet
COPY . /home/user/ft_ping

# Définir le répertoire de travail
WORKDIR /home/user/ft_ping

# Compiler le projet et la bibliothèque associée
RUN make -C libft

RUN make

# Démarrer un shell par défaut
CMD ["/bin/bash"]
