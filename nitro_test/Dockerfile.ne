FROM amazonlinux:2

COPY libnsm.so /lib64/
COPY bootstrap.sh /usr/bin/
COPY enclave /usr/bin/

CMD ["/usr/bin/bootstrap.sh"]
