# traceroute
Send udp packet to <Host|Ip>  
The command is protocole independant and can be used for both Ipv4 and Ipv6.  
The aim is to trace the route between your host and the target you are looking for.  
Is it possible by using ttl and hop limit field to receive from each gateway crossed an ICMP Packet TTL_EXCEEDED.  
The udp packet is mapped to a destination port probably unused, thereby we can receive a last ICMP Packet ICMP_DEST_UNREACH.  
By default a each setting three probes are sent but you can configure it and many other options like this :    
-q Number: send Number probes at each ttl settings  
-w Number: set Number seconds before a request timeout  
-p Number: port destination is set to Number  
-m Number: set the max TTL to Number  
-f Number: set the first TTL to Number  
