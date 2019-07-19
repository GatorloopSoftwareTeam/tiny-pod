function power_consumption_tinypod(t_idling,t_running)
% Simulation of tinypod power consumption, including idling phase and running phase
% Author: Duan Tu
% July 17, 2019


% Idling phase: P_idling, E_idling    

% Microcontroller: 		1* 45.1mA * 7.5V = 45.1*10^-3 A * 7.5V = 0.33825 w
% 
% BNO055 Intelligent 9-axis absolute orientation sensor: 
% 2* 12.3 mA * 7.5V = 2* 12.3*10^(-3) A * 7.5V = 0.1845 w
% 
% Voltage Sensor:
% 1*0.00375 mA * 7.5V = 0.00375 *10^(-3) A * 7.5V =  2.8125*10^(-5) w
% To sum up,
% 		
% Equation: 	
% P_idling = (0.33825 w+ 0.1845 w+ 2.8125*10^(-5) w)*t
%          = 0.522778125 w	
% 		E_idling = 0.522778125 w * t_idling 



% Running phase: P_running, E_running
% 
% P_running = P_idling + P_motor 
% 
% P_motor = 4* 200 million mA * 7.5 V = 4*200, 000 A * 7.5 V = 6000000 w 
% P_running = 0.522778125 w + 6000000 w  = 6.000000522778125e+06 w
% 							 
% 
% E_running = 6.000000522778125e+06 w * t_running  



% INSTRUCTION
% please input time in terms of seconds 

 

fe_i = @(t) (0.522778125*t)/(3.6*10^6); % energy consumption during idling (kWh)
fe_r = @(t) (6.000000522778125*10^(6)*t)/(3.6*10^6); % energy consumption when running (kWh)

% calculate power consumption for each phase with given time value 
e_idling = fe_i(t_idling);
e_running = fe_r(t_running);
e_total = e_idling + e_running;

% print out result 
fprintf('If the pod idles for %d seconds and then runs for %d seconds,', t_idling, t_running);
fprintf(' power consumption of the pod is %f kWh. during idling and %f kWh during running. ',e_idling,e_running);
fprintf('\nIn total, power consumption of the pod is %f kWh. ',e_total);

end