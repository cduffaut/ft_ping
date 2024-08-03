# [TO DO LIST]

- backup les exit et free 
- Voir s'il respecte à 100% le sujet.
- Les erreurs de program ne devraient pas être imprimé si pas spécifique à ping (seulement)
	affichées avec "-v"

[info] The default initial TTL value for Linux/Unix is 64
[info] Struct icmphdr représqente l'entête d'un paquet icmphdr

[ERROR_MESSAGE_TO_VERIF] 
se renseginer sur stddev : val "nan" pourquoi ?

# avoir accès au terminal du docker:
docker build -t ft-ping .

docker run --rm -it --cap-add=ALL --name ping ft-ping /bin/bash

verifier les leaks:

valgrind --leak-check=full ./ft_ping google.com

# For the options:
  	-v
	Indique le fait qu'un programme ou une commande affiche explicitement toutes les opérations effectuées.

	The -v option here will also allow us to see the results in case of a
	problem or an error linked to the packets, which logically shouldn’t
	force the program to stop (the modification of the TTL value can help
	to force an error).

	-?
	Affiche l'aide à l'invite de commandes.

# ATTENTION:

- droit utilisateur: si non root > mettre message d'erreur
- la fonction control C doit quitter proprement et afficher un rapport

# Vocabulaire à aller chercher:
- DNS: The Domain Name System (DNS) is a hierarchical and distributed name service that provides a naming system for computers, services, and other resources on the Internet or other Internet Protocol (IP) networks.

src: https://en.wikipedia.org/wiki/Domain_Name_System

- checksum: A checksum is a value that represents the number of bits in a transmission message and is used by IT professionals to detect high-level errors within data transmissions. 

src: https://www.techtarget.com/searchsecurity/definition/checksum

# Explications sur l'affichage de la commande PING:
TTL means “time to live.” This information shows you the total routers the packet will travel through before stopping.

(If you see “request timed out,” it tells you that the packets couldn’t find the host, which indicates a connection problem.)

The Ping statistics section shows the overall (global) numbers for the process. The packets line shows the number of packets sent and received, and tells you if any were lost. If they were, there’s like a connection issue.

Lastly, approximate round trip times show the connection speed. The higher the time, the worse the connection.

src: https://www.pagerduty.com/resources/learn/ping-network-testing-connectivity/#:~:text=Understanding%20Ping%20results,-All%20of%20those&text=The%20first%20thing%20you'll,response%20time%20from%20the%20server.
