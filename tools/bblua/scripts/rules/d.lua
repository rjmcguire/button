--[[
 Copyright: Copyright Jason White, 2016
 License:   MIT
 Authors:   Jason White

 Description:
 Returns the appropriate tool chain for the current platform.
]]

-- For D, this is always DMD.
return require("rules.d.dmd")