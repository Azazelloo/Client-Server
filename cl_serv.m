%%%%client%%%%%
% t=tcpip('192.168.0.16', 4555, 'NetworkRole', 'client');
% fopen(t);
% data='blablabla';
% fwrite(t, data, 'char');

%%%%server%%%%%
 clc
 clear
 close all
% рабочее подключение UDP
 t=udp('192.168.0.16',4554);
 fopen(t);
 fwrite(t,'Connect!');
 
t.Timeout=3;
ex='exit'; a='';
while(~strcmp(a,ex))
    %a = fscanf(t,'%s');
    a=fgets(t)
    %fprintf('%s',a);
    switch a
        case 'sin'
            fprintf('Plot sin!');
            figure
            axes
            plot(sin(-pi:pi/500:pi))
            drawnow
            fwrite(t, 'Plot sin is done! ', 'char');
        case 'cos'
            fprintf('Plot cos!');
            figure
            axes
            plot(cos(-pi:pi/500:pi))
            drawnow
            fwrite(t, 'Plot cos is done! ', 'char');
        case 'tan'
            fprintf('Plot tan!');
            figure
            axes
            plot(tan(-pi:pi/500:pi))
            drawnow
            fwrite(t, 'Plot tan is done! ', 'char');
        case 'exit'
            fprintf('Server off!');
            fwrite(t, 'off! ', 'char');
            break;
        otherwise
            fprintf('Input error!');
            if(a~=0)
            fwrite(t, 'Input error!', 'char');
            end
    end
end
fclose(t);

 
%  рабочее подключение TCP/IP
%  t=tcpip('192.168.0.16', 4555, 'NetworkRole', 'server'); 
%  fopen(t); %соединение с клиентом
%  fprintf('Connected!');
%  t.Timeout=3;

% ex='exit'; a='';
% while(~strcmp(a,ex))
%     %a = fscanf(t,'%s');
%     a=fgets(t);
%     %fprintf('%s',a);
%     switch a
%         case 'sin'
%             fprintf('Plot sin!');
%             figure
%             axes
%             plot(sin(-pi:pi/500:pi))
%             drawnow
%             fwrite(t, 'Plot sin is done! ', 'char');
%         case 'cos'
%             fprintf('Plot cos!');
%             figure
%             axes
%             plot(cos(-pi:pi/500:pi))
%             drawnow
%             fwrite(t, 'Plot cos is done! ', 'char');
%         case 'tan'
%             fprintf('Plot tan!');
%             figure
%             axes
%             plot(tan(-pi:pi/500:pi))
%             drawnow
%             fwrite(t, 'Plot tan is done! ', 'char');
%         case 'exit'
%             fprintf('Server off!');
%             fwrite(t, 'off! ', 'char');
%             break;
%         otherwise
%             if(a~=0)
%             fwrite(t, 'Input error! ', 'char');
%             end
%     end
% end
% echoudp('off');
% fclose(t);


